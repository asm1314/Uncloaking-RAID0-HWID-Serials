#include <Windows.h>
#include <iostream>

#define IOCTL_SCSI_MINIPORT 0x0004D008

#define IOCTL_HEADER SRB_IO_CONTROL
#define INTEL_SIGNATURE "IntelRdp"

#define INTEL_TIMEOUT 0x1F4
#define IOCTL_GET_DICTIONARY_VALUES 0x90000A04

#define INTEL_FIELD_ID_SERIAL 0x45440004
#define INTEL_FIELD_ID_SERIAL_LENGTH 0x45440005

#define INTEL_FIELD_TYPE_STRING 0x0A
#define INTEL_FIELD_TYPE_DWORD 0x02

#define MAX_SERIAL_LENGTH 41

typedef struct _INTEL_DICTIONARY_FIELD
{
	DWORD Id;
	DWORD Type;
} INTEL_DICTIONARY_FIELD;

typedef struct _SRB_IO_CONTROL
{
	ULONG HeaderLength;
	UCHAR Signature[8];
	ULONG Timeout;
	ULONG ControlCode;
	ULONG ReturnCode;
	ULONG Length;
} SRB_IO_CONTROL;


typedef struct _INTEL_SERIALS_REQUEST
{
	IOCTL_HEADER IoctlHeader;
	DWORD Unknown1;                   // 0x08 ? maybe field request size?
	DWORD FieldsOffset;               // 0x30 -
	DWORD Count;                      // 0x0E - number of requested dictionary fields
	DWORD DataBufferOffset;           // 0xA0 - offset from start of entire buffer
	DWORD Padding1;                   // ----
	INTEL_DICTIONARY_FIELD Fields[2]; // 
	UCHAR bDataBuffer[1];             // 
} INTEL_SERIALS_REQUEST, * PINTEL_SERIALS_REQUEST;


void
swap_endianess(PCHAR dest, PCHAR src);

HANDLE
get_scsi_handle(int port)
{
	char scsi_path[MAX_PATH]{};
	if (sprintf_s(scsi_path, R"(\\.\Scsi%i:)", port) == -1) {
		return INVALID_HANDLE_VALUE;
	}

	return CreateFileA(
		scsi_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr, OPEN_EXISTING, 0, nullptr
	);
}

bool
print_serials(HANDLE scsi_handle)
{
	const auto buffer_size = offsetof(INTEL_SERIALS_REQUEST, bDataBuffer) + 0xF000; // arbitrary amount of data for the response
	auto* buffer = static_cast<INTEL_SERIALS_REQUEST*>(VirtualAlloc(nullptr, buffer_size, MEM_COMMIT, PAGE_READWRITE));
	if (buffer == nullptr) {
		return false;
	}

	memset(buffer, 0, buffer_size);

	buffer->IoctlHeader.HeaderLength = sizeof(IOCTL_HEADER);
	memcpy_s(
		reinterpret_cast<char*>(&buffer->IoctlHeader.Signature), sizeof(buffer->IoctlHeader.Signature),
		INTEL_SIGNATURE, sizeof(buffer->IoctlHeader.Signature)
	);

	buffer->IoctlHeader.Timeout = INTEL_TIMEOUT;
	buffer->IoctlHeader.ControlCode = IOCTL_GET_DICTIONARY_VALUES;
	buffer->IoctlHeader.ReturnCode = 0;
	buffer->IoctlHeader.Length = static_cast<ULONG>(buffer_size) - sizeof(IOCTL_HEADER);

	buffer->Unknown1 = 8; // might be the size of a field request (two dwords)
	buffer->FieldsOffset = offsetof(INTEL_SERIALS_REQUEST, Fields);
	buffer->Count = _countof(buffer->Fields);
	buffer->DataBufferOffset = offsetof(INTEL_SERIALS_REQUEST, bDataBuffer);

	buffer->Fields[0].Id = INTEL_FIELD_ID_SERIAL_LENGTH;
	buffer->Fields[0].Type = INTEL_FIELD_TYPE_DWORD;

	buffer->Fields[1].Id = INTEL_FIELD_ID_SERIAL;
	buffer->Fields[1].Type = INTEL_FIELD_TYPE_STRING;


	DWORD bytes_returned{};
	if (DeviceIoControl(scsi_handle, IOCTL_SCSI_MINIPORT,
		buffer, buffer_size,
		buffer, buffer_size,
		&bytes_returned, nullptr) == FALSE
		) {
		VirtualFree(buffer, 0, MEM_RELEASE);
		return false;
	}

	if (buffer->IoctlHeader.ReturnCode != ERROR_SUCCESS) {
		VirtualFree(buffer, 0, MEM_RELEASE);
		return false;
	}

	auto* response = reinterpret_cast<char*>(buffer) + offsetof(INTEL_SERIALS_REQUEST, bDataBuffer);

	for (int i = 0; i < static_cast<int>(buffer_size - 24); ++i) {
		if (
			*reinterpret_cast<DWORD*>(&response[i]) != INTEL_FIELD_ID_SERIAL_LENGTH ||
			*reinterpret_cast<DWORD*>(&response[i] + 12) != INTEL_FIELD_ID_SERIAL
			) {
			continue;
		}

		auto serial_length = *reinterpret_cast<DWORD*>(&response[i] + 8);
		auto* serial = &response[i] + 20;

		char fixed_serial[MAX_SERIAL_LENGTH]{};
		swap_endianess(fixed_serial, serial);

		printf("SerialNumber: \"%s\"\n", fixed_serial);

		i += 20 + serial_length;
	}

	VirtualFree(buffer, 0, MEM_RELEASE);
	return true;
}

void
swap_endianess(PCHAR dest, PCHAR src)
{
	for (size_t i = 0, l = strlen(src); i < l; i += 2) {
		dest[i] = src[i + 1];
		dest[i + 1] = src[i];
	}
}

int
main()
{
	for (auto scsi_port = 0; scsi_port < 16; ++scsi_port) {
		auto scsi_handle = get_scsi_handle(scsi_port);
		if (scsi_handle == INVALID_HANDLE_VALUE) {
			continue;
		}

		print_serials(scsi_handle);

		CloseHandle(scsi_handle);
	}

	system("pause");
	return 0;
}
