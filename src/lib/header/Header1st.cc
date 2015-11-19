#include "Header1st.hh"
#include "../util/endian.h"
#include "../util/checksum.h"


namespace fw {


bool Header1st::_valid(const uint8_t *const data, const size_t data_len) const {
    // calculate check sum, skip the csum, start from the 3rd byte
    return (csum_LEU16_U16(data + sizeof(uint16_t), get_blk_len()) == _csum);
}


void Header1st::_read(const uint8_t *const data) {
    GET_U16_LE(_csum, data, 0);
    GET_U16_LE(_len, data + sizeof(_csum), 0);
    _len_dec = (_len & (uint16_t)0x0FFF);
}


void Header1st::_write(uint8_t *data) const {
    PUT_U16_LE(_csum, data                , 0);
    PUT_U16_LE(_len , data + sizeof(_csum), 0);
}


}
