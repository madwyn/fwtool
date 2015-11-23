#include "Header3rd.hh"

#include <zlib.h>


namespace fw {


bool Header3rd::_valid(const uint8_t *const data, const size_t data_len) const {
    bool ret = false;

    uint8_t *buf = (uint8_t *)malloc(data_len);

    if (nullptr != buf) {
        memcpy(buf, data, data_len);

        *(uint32_t*)(buf + FDAT_IMAGE_HEADER_LEN) = 0x00000000;   // set the magic u32

        uint32_t crc = (uint32_t)crc32(0, buf + sizeof(HEADER_U32_CRC), FDAT_IMAGE_HEADER_LEN - FDAT_IMAGE_MAGIC_LEN - sizeof(HEADER_U16_CSUM));

        ret = _crc == crc;

        free(buf);
    }

    return ret;
}


void Header3rd::_read(const uint8_t *const data) {
    HEADER_U32_CRC *p = (HEADER_U32_CRC *)data;
    _crc = p->crc;
    _payload = (uint8_t *)data + sizeof(HEADER_U16_CSUM);
}


void Header3rd::_write(uint8_t *data) const {

}


}
