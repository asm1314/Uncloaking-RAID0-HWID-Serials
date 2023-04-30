#include <Windows.h>
#include <iostream>

#define IOCTL_SCSI_MINIPORT 0x0004D008

typedef struct _SRB_IO_CONTROL
{
    ULONG HeaderLength;
    UCHAR Signature[8];
    ULONG Timeout;
    ULONG ControlCode;
    ULONG ReturnCode;
    ULONG Length;
} SRB_IO_CONTROL;

#pragma pack(1)

struct ATA_IDENTIFY_DEVICE
{
    WORD GeneralConfiguration;                  //0
    WORD LogicalCylinders;                      //1	Obsolete
    WORD SpecificConfiguration;                 //2
    WORD LogicalHeads;                          //3 Obsolete
    WORD Retired1[2];                           //4-5
    WORD LogicalSectors;                        //6 Obsolete
    DWORD ReservedForCompactFlash;              //7-8
    WORD Retired2;                              //9
    CHAR SerialNumber[20];                      //10-19
    WORD Retired3;                              //20
    WORD BufferSize;                            //21 Obsolete
    WORD Obsolute4;                             //22
    CHAR FirmwareRev[8];                        //23-26
    CHAR Model[40];                             //27-46
    WORD MaxNumPerInterupt;                     //47
    WORD Reserved1;                             //48
    WORD Capabilities1;                         //49
    WORD Capabilities2;                         //50
    DWORD Obsolute5;                            //51-52
    WORD Field88and7064;                        //53
    WORD Obsolute6[5];                          //54-58
    WORD MultSectorStuff;                       //59
    DWORD TotalAddressableSectors;              //60-61
    WORD Obsolute7;                             //62
    WORD MultiWordDma;                          //63
    WORD PioMode;                               //64
    WORD MinMultiwordDmaCycleTime;              //65
    WORD RecommendedMultiwordDmaCycleTime;      //66
    WORD MinPioCycleTimewoFlowCtrl;             //67
    WORD MinPioCycleTimeWithFlowCtrl;           //68
    WORD Reserved2[6];                          //69-74
    WORD QueueDepth;                            //75
    WORD SerialAtaCapabilities;                 //76
    WORD SerialAtaAdditionalCapabilities;       //77
    WORD SerialAtaFeaturesSupported;            //78
    WORD SerialAtaFeaturesEnabled;              //79
    WORD MajorVersion;                          //80
    WORD MinorVersion;                          //81
    WORD CommandSetSupported1;                  //82
    WORD CommandSetSupported2;                  //83
    WORD CommandSetSupported3;                  //84
    WORD CommandSetEnabled1;                    //85
    WORD CommandSetEnabled2;                    //86
    WORD CommandSetDefault;                     //87
    WORD UltraDmaMode;                          //88
    WORD TimeReqForSecurityErase;               //89
    WORD TimeReqForEnhancedSecure;              //90
    WORD CurrentPowerManagement;                //91
    WORD MasterPasswordRevision;                //92
    WORD HardwareResetResult;                   //93
    WORD AcoustricManagement;                   //94
    WORD StreamMinRequestSize;                  //95
    WORD StreamingTimeDma;                      //96
    WORD StreamingAccessLatency;                //97
    DWORD StreamingPerformance;                 //98-99
    ULONGLONG MaxUserLba;                       //100-103
    WORD StremingTimePio;                       //104
    WORD Reserved3;                             //105
    WORD SectorSize;                            //106
    WORD InterSeekDelay;                        //107
    WORD IeeeOui;                               //108
    WORD UniqueId3;                             //109
    WORD UniqueId2;                             //110
    WORD UniqueId1;                             //111
    WORD Reserved4[4];                          //112-115
    WORD Reserved5;                             //116
    DWORD WordsPerLogicalSector;                //117-118
    WORD Reserved6[8];                          //119-126
    WORD RemovableMediaStatus;                  //127
    WORD SecurityStatus;                        //128
    WORD VendorSpecific[31];                    //129-159
    WORD CfaPowerMode1;                         //160
    WORD ReservedForCompactFlashAssociation[7]; //161-167
    WORD DeviceNominalFormFactor;               //168
    WORD DataSetManagement;                     //169
    WORD AdditionalProductIdentifier[4];        //170-173
    WORD Reserved7[2];                          //174-175
    CHAR CurrentMediaSerialNo[60];              //176-205
    WORD SctCommandTransport;                   //206
    WORD ReservedForCeAta1[2];                  //207-208
    WORD AlignmentOfLogicalBlocks;              //209
    DWORD WriteReadVerifySectorCountMode3;      //210-211
    DWORD WriteReadVerifySectorCountMode2;      //212-213
    WORD NvCacheCapabilities;                   //214
    DWORD NvCacheSizeLogicalBlocks;             //215-216
    WORD NominalMediaRotationRate;              //217
    WORD Reserved8;                             //218
    WORD NvCacheOptions1;                       //219
    WORD NvCacheOptions2;                       //220
    WORD Reserved9;                             //221
    WORD TransportMajorVersionNumber;           //222
    WORD TransportMinorVersionNumber;           //223
    WORD ReservedForCeAta2[10];                 //224-233
    WORD MinimumBlocksPerDownloadMicrocode;     //234
    WORD MaximumBlocksPerDownloadMicrocode;     //235
    WORD Reserved10[19];                        //236-254
    WORD IntegrityWord;                         //255
};

#pragma pack()

#define IOCTL_HEADER SRB_IO_CONTROL

#define CSMI_SAS_SIGNATURE    "CSMISAS"
#define CSMI_SAS_TIMEOUT      60

#define CC_CSMI_SAS_GET_PHY_INFO       20
#define CC_CSMI_SAS_SET_PHY_INFO       21
#define CC_CSMI_SAS_GET_LINK_ERRORS    22
#define CC_CSMI_SAS_SMP_PASSTHRU       23
#define CC_CSMI_SAS_SSP_PASSTHRU       24
#define CC_CSMI_SAS_STP_PASSTHRU       25
#define CC_CSMI_SAS_GET_SATA_SIGNATURE 26
#define CC_CSMI_SAS_GET_SCSI_ADDRESS   27
#define CC_CSMI_SAS_GET_DEVICE_ADDRESS 28
#define CC_CSMI_SAS_TASK_MANAGEMENT    29
#define CC_CSMI_SAS_GET_CONNECTOR_INFO 30
#define CC_CSMI_SAS_GET_LOCATION       31

#define CSMI_SAS_LINK_RATE_NEGOTIATED  0x00
#define CSMI_SAS_LINK_RATE_1_5_GBPS    0x08
#define CSMI_SAS_LINK_RATE_3_0_GBPS    0x09
#define CSMI_SAS_LINK_RATE_6_0_GBPS    0x0A
#define CSMI_SAS_LINK_RATE_12_0_GBPS   0x0B

#define CSMI_SAS_STP_READ           0x00000001
#define CSMI_SAS_STP_WRITE          0x00000002
#define CSMI_SAS_STP_UNSPECIFIED    0x00000004
#define CSMI_SAS_STP_PIO            0x00000010
#define CSMI_SAS_STP_DMA            0x00000020
#define CSMI_SAS_STP_PACKET         0x00000040
#define CSMI_SAS_STP_DMA_QUEUED     0x00000080
#define CSMI_SAS_STP_EXECUTE_DIAG   0x00000100
#define CSMI_SAS_STP_RESET_DEVICE   0x00000200

#define CSMI_SAS_PHY_UNUSED               0x00
#define CSMI_SAS_NO_DEVICE_ATTACHED       0x00
#define CSMI_SAS_END_DEVICE               0x10
#define CSMI_SAS_EDGE_EXPANDER_DEVICE     0x20
#define CSMI_SAS_FANOUT_EXPANDER_DEVICE   0x30

#define CSMI_SAS_STATUS_SUCCESS 0
#define CSMI_SAS_STATUS_FAILED 1
#define CSMI_SAS_STATUS_BAD_CNTL_CODE 2
#define CSMI_SAS_STATUS_INVALID_PARAMETER 3
#define CSMI_SAS_STATUS_WRITE_ATTEMPTED 4

typedef struct _CSMI_SAS_IDENTIFY
{
    UCHAR bDeviceType;
    UCHAR bRestricted;
    UCHAR bInitiatorPortProtocol;
    UCHAR bTargetPortProtocol;
    UCHAR bRestricted2[8];
    UCHAR bSASAddress[8];
    UCHAR bPhyIdentifier;
    UCHAR bSignalClass;
    UCHAR bReserved[6];
} CSMI_SAS_IDENTIFY, *PCSMI_SAS_IDENTIFY;

typedef struct _CSMI_SAS_PHY_ENTITY
{
    CSMI_SAS_IDENTIFY Identify;
    UCHAR bPortIdentifier;
    UCHAR bNegotiatedLinkRate;
    UCHAR bMinimumLinkRate;
    UCHAR bMaximumLinkRate;
    UCHAR bPhyChangeCount;
    UCHAR bAutoDiscover;
    UCHAR bPhyFeatures;
    UCHAR bReserved;
    CSMI_SAS_IDENTIFY Attached;
} CSMI_SAS_PHY_ENTITY, *PCSMI_SAS_PHY_ENTITY;

typedef struct _CSMI_SAS_PHY_INFO
{
    UCHAR bNumberOfPhys;
    UCHAR bReserved[3];
    CSMI_SAS_PHY_ENTITY Phy[32];
} CSMI_SAS_PHY_INFO, *PCSMI_SAS_PHY_INFO;

typedef struct _CSMI_SAS_PHY_INFO_BUFFER
{
    IOCTL_HEADER IoctlHeader;
    CSMI_SAS_PHY_INFO Information;
} CSMI_SAS_PHY_INFO_BUFFER, *PCSMI_SAS_PHY_INFO_BUFFER;

typedef struct _CSMI_SAS_STP_PASSTHRU
{
    UCHAR bPhyIdentifier;
    UCHAR bPortIdentifier;
    UCHAR bConnectionRate;
    UCHAR bReserved;
    UCHAR bDestinationSASAddress[8];
    UCHAR bReserved2[4];
    UCHAR bCommandFIS[20];
    ULONG uFlags;
    ULONG uDataLength;
} CSMI_SAS_STP_PASSTHRU, *PCSMI_SAS_STP_PASSTHRU;

typedef struct _CSMI_SAS_STP_PASSTHRU_STATUS
{
    UCHAR bConnectionStatus;
    UCHAR bReserved[3];
    UCHAR bStatusFIS[20];
    ULONG uSCR[16];
    ULONG uDataBytes;
} CSMI_SAS_STP_PASSTHRU_STATUS, *PCSMI_SAS_STP_PASSTHRU_STATUS;

typedef struct _CSMI_SAS_STP_PASSTHRU_BUFFER
{
    IOCTL_HEADER IoctlHeader;
    CSMI_SAS_STP_PASSTHRU Parameters;
    CSMI_SAS_STP_PASSTHRU_STATUS Status;
    UCHAR bDataBuffer[1];
} CSMI_SAS_STP_PASSTHRU_BUFFER, *PCSMI_SAS_STP_PASSTHRU_BUFFER;


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
get_sas_phy_info(HANDLE scsi_handle, CSMI_SAS_PHY_INFO * result)
{
    CSMI_SAS_PHY_INFO_BUFFER phy_info_buffer{};
    phy_info_buffer.IoctlHeader.HeaderLength = sizeof(IOCTL_HEADER);
    strncpy_s(
        reinterpret_cast<char*>(phy_info_buffer.IoctlHeader.Signature), sizeof(phy_info_buffer.IoctlHeader.Signature),
        CSMI_SAS_SIGNATURE, sizeof(phy_info_buffer.IoctlHeader.Signature)
    );

    phy_info_buffer.IoctlHeader.Timeout = CSMI_SAS_TIMEOUT;
    phy_info_buffer.IoctlHeader.ControlCode = CC_CSMI_SAS_GET_PHY_INFO;
    phy_info_buffer.IoctlHeader.ReturnCode = 0;
    phy_info_buffer.IoctlHeader.Length = sizeof(phy_info_buffer) - sizeof(IOCTL_HEADER);


    DWORD bytes_returned{};
    if (DeviceIoControl(scsi_handle, IOCTL_SCSI_MINIPORT,
                        &phy_info_buffer, sizeof(phy_info_buffer),
                        &phy_info_buffer, sizeof(phy_info_buffer),
                        &bytes_returned, nullptr) == FALSE
    ) {
        const auto error_code = GetLastError();
        if (error_code == ERROR_INVALID_FUNCTION || error_code == ERROR_NOT_SUPPORTED || error_code == ERROR_DEV_NOT_EXIST) {
            return false;
        }

        SetLastError(ERROR_SUCCESS);
    }

    if (phy_info_buffer.IoctlHeader.ReturnCode != CSMI_SAS_STATUS_SUCCESS) {
        return false;
    }

    *result = phy_info_buffer.Information;
    return true;
}

bool
get_sas_identify_device(HANDLE scsi_handle, const CSMI_SAS_PHY_ENTITY * entity, ATA_IDENTIFY_DEVICE * result)
{
    const auto buffer_size = sizeof(CSMI_SAS_STP_PASSTHRU_BUFFER) + sizeof(ATA_IDENTIFY_DEVICE);
    auto * buffer = static_cast<CSMI_SAS_STP_PASSTHRU_BUFFER*>(VirtualAlloc(nullptr, buffer_size, MEM_COMMIT, PAGE_READWRITE));
    if (buffer == nullptr) {
        return false;
    }

    buffer->Parameters.bPhyIdentifier = entity->Attached.bPhyIdentifier;
    buffer->Parameters.bPortIdentifier = entity->bPortIdentifier;
    buffer->Parameters.bConnectionRate = CSMI_SAS_LINK_RATE_NEGOTIATED;
    buffer->Parameters.uFlags = CSMI_SAS_STP_PIO | CSMI_SAS_STP_READ;
    memcpy(buffer->Parameters.bDestinationSASAddress, entity->Attached.bSASAddress, sizeof(entity->Attached.bSASAddress));

    buffer->Parameters.uDataLength = sizeof(ATA_IDENTIFY_DEVICE);
    buffer->Parameters.bCommandFIS[0] = 0x27; // Type: host-to-device FIS
    buffer->Parameters.bCommandFIS[1] = 0x80; // Bit7: Update command register

    buffer->Parameters.bCommandFIS[2] = ID_CMD;
    buffer->Parameters.bCommandFIS[3] = 0;
    buffer->Parameters.bCommandFIS[4] = 0;
    buffer->Parameters.bCommandFIS[5] = 0;
    buffer->Parameters.bCommandFIS[6] = 0;
    buffer->Parameters.bCommandFIS[7] = 0xA0; // target
    buffer->Parameters.bCommandFIS[8] = 0;
    buffer->Parameters.bCommandFIS[9] = 0;
    buffer->Parameters.bCommandFIS[10] = 0;
    buffer->Parameters.bCommandFIS[11] = 0;
    buffer->Parameters.bCommandFIS[12] = 0;
    buffer->Parameters.bCommandFIS[13] = 0;


    buffer->IoctlHeader.HeaderLength = sizeof(IOCTL_HEADER);
    strncpy_s(
        reinterpret_cast<char*>(&buffer->IoctlHeader.Signature), sizeof(buffer->IoctlHeader.Signature),
        CSMI_SAS_SIGNATURE, sizeof(buffer->IoctlHeader.Signature)
    );
    buffer->IoctlHeader.Timeout = CSMI_SAS_TIMEOUT;
    buffer->IoctlHeader.ControlCode = CC_CSMI_SAS_STP_PASSTHRU;
    buffer->IoctlHeader.ReturnCode = 0;
    buffer->IoctlHeader.Length = static_cast<ULONG>(buffer_size) - sizeof(IOCTL_HEADER);

    DWORD bytes_returned{};
    if (DeviceIoControl(scsi_handle, IOCTL_SCSI_MINIPORT,
                        buffer, buffer_size,
                        buffer, buffer_size,
                        &bytes_returned, nullptr) == FALSE
    ) {
        const auto error_code = GetLastError();
        if (error_code == ERROR_INVALID_FUNCTION || error_code == ERROR_NOT_SUPPORTED || error_code == ERROR_DEV_NOT_EXIST) {
            VirtualFree(buffer, 0, MEM_RELEASE);
            return false;
        }

        SetLastError(ERROR_SUCCESS);
    }

    if (buffer->IoctlHeader.ReturnCode != CSMI_SAS_STATUS_SUCCESS) {
        return false;
    }

    *result = *reinterpret_cast<ATA_IDENTIFY_DEVICE*>(&buffer->bDataBuffer);

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

        CSMI_SAS_PHY_INFO phy_info{};
        if (!get_sas_phy_info(scsi_handle, &phy_info)) {
            printf("!! get_sas_phy_info failed for scsi_port %i with error %lx\n", scsi_port, GetLastError());
            continue;
        }

        printf("scsi_port %i can support %i devices\n", scsi_port, phy_info.bNumberOfPhys);


        for (auto device_index = 0; device_index < phy_info.bNumberOfPhys; ++device_index) {
            const auto * sas_phy_entity = &phy_info.Phy[device_index];
            if (sas_phy_entity->Attached.bDeviceType != CSMI_SAS_END_DEVICE) {
                continue;
            }

            ATA_IDENTIFY_DEVICE identify{};
            if (!get_sas_identify_device(scsi_handle, sas_phy_entity, &identify)) {
                printf("!! get_sas_identify_device failed for scsi_port %i with error %lx\n", scsi_port, GetLastError());
                continue;
            }

            char serial_number[sizeof(identify.SerialNumber) + 1]{};
            swap_endianess(serial_number, identify.SerialNumber);
            printf("SerialNumber: \"%s\"\n", serial_number);
        }

        CloseHandle(scsi_handle);
    }
}
