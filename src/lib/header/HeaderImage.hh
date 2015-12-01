#ifndef FWT_HEADERIMAGE_HH
#define FWT_HEADERIMAGE_HH

#include <stdint.h>

#include "fdat_def.h"


namespace fw {


#define FDAT_HDR_VERSION_LEN    4
#define MAX_FDAT_FS_IMAGES      28
#define FDAT_IMAGE_HDR_LEN      0x200


typedef struct {
    uint8_t     ident;                                  // 0000
    uint8_t     unknown_01[3];                          // 0001
    uint32_t    fs_offset;                              // 0004 - offset to filesystem image
    uint32_t    fs_length;                              // 0008 - length of filesystem image
    uint32_t    unknown_02;                             // 000c
} FDAT_FS_IMAGE_DESC;


typedef struct {
    uint8_t     magic[FDAT_IMAGE_MAGIC_LEN];            // 0000
    uint32_t    header_crc;                             // 0008 - CRC32 of remainder of header (000c-01ff)
    uint8_t     image_version[FDAT_HDR_VERSION_LEN];    // 000c - "0100" - I assume this is a version string
    uint8_t     fw_mode_type;                           // 0010 - ModeType: "P" (??? "U" in all fw ?)
    uint8_t     fw_mode_type_unknown_pad[3];            // 0011
    uint8_t     fw_luw_flag;                            // 0014 - LUW flag: "N"
    uint8_t     fw_luw_flag_unknown_pad[3];             // 0015
    uint32_t    unknown_01;                             // 0018 - unknown
    uint32_t    unknown_02;                             // 001c - unknown
    uint8_t     version_minor;                          // 0020 - minor version: FF is sign-extended on read
    uint8_t     version_major;                          // 0021 - major version: FF is sign-extended on read
    uint8_t     version_unknown_pad[2];                 // 0022
    uint32_t    model;                                  // 0024 - body or lens model (see table in fwt_util.c)
    uint32_t    unknown_03;                             // 0028 - unknown uint32_t
    uint32_t    unknown_04;                             // 002c
    uint32_t    fw_offset;                              // 0030 - offset to firmware image (.tar)
    uint32_t    fw_length;                              // 0034 - length of firmware image (.tar)
    uint32_t    fs_image_count;                         // 0038 - number of fs images starting at 0040
    uint32_t    unknown_05;                             // 003c

    FDAT_FS_IMAGE_DESC fs_image_info[MAX_FDAT_FS_IMAGES];
} FDAT_IMAGE_HEADER;


class HeaderImage {
public:
    uint32_t _crc           = 0;
    uint32_t _len           = 0;
    uint32_t _offset        = 0;
    uint32_t _image_count   = 0;

    void read(const uint8_t *const data);
    bool valid(const uint8_t *const data);
};


}


#endif //FWT_HEADERIMAGE_HH
