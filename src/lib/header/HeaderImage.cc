#include <string.h>
#include <zlib.h>
#include <stdlib.h>
#include "HeaderImage.hh"
#include "../util/print_tool.h"
#include "../util/endian.h"


namespace fw {


bool HeaderImage::valid(const uint8_t *const data) {
    bool ret = false;

    const FDAT_IMAGE_HEADER *header = (const FDAT_IMAGE_HEADER *)data;

    if (0 == memcmp(header->magic, FDAT_IMAGE_MAGIC, FDAT_IMAGE_MAGIC_LEN)) {
        uint8_t *buf = (uint8_t *)malloc(FDAT_IMAGE_HDR_LEN);
        memcpy(buf, data, FDAT_IMAGE_HDR_LEN);

        header = (FDAT_IMAGE_HEADER *)buf;

        const uint8_t *header_data     = (const uint8_t *)(header->image_version);
        const size_t   header_data_len = FDAT_IMAGE_HDR_LEN - sizeof(header->magic) - sizeof(header->header_crc);

        *(uint32_t*)(header_data + header_data_len - 4) = 0x00000000;   // set the magic u32

        uint32_t crc = (uint32_t)crc32(0, header_data, header_data_len);

        ret = (crc == _crc);

        free(buf);
    }

    return ret;
}


void HeaderImage::read(const uint8_t *const data) {
    FDAT_IMAGE_HEADER *header = (FDAT_IMAGE_HEADER *)data;

    _crc = header->header_crc;

    GET_U32_LE(_len        , (uint8_t *)(&(header->fw_length)), 0);
    GET_U32_LE(_offset     , (uint8_t *)(&(header->fw_offset)), 0);
    GET_U32_LE(_image_count, (uint8_t *)(&(header->fw_length)), 0);
}


}
