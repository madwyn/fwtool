#include "Header3rd.hh"

#include <zlib.h>


namespace fw {


bool Header3rd::_valid(const uint8_t *const data, const size_t data_len) const {
    return true;
}


void Header3rd::_read(const uint8_t *const data) {
    _len_dec = get_blk_len(); // todo: this is not right, because we cannot decode it yet
    _payload = (uint8_t *)data + sizeof(HEADER_U16_CSUM);
}


void Header3rd::_write(uint8_t *data) const {

}


}
