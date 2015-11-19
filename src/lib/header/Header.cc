#include "Header.hh"
#include "fdata_def.h"


namespace fw {


MSG_CODE Header::valid(const uint8_t *const data_enc, const size_t data_len) {
    MSG_CODE ret     = MSG_OK;
    size_t   buf_len = get_blk_len();
    uint8_t *buf     = (uint8_t *)malloc(buf_len);

    if (nullptr != buf) {
        // decode the message
        if (MSG_OK == _cypher->dec(data_enc, buf, buf_len)) {
            Magic magic;

            // verify the decrypted header
            if (magic.valid(buf + sizeof(HEADER_U16_CSUM))) {
                _read(buf);

                ret = _valid(buf, data_len) ? MSG_OK : HEADER_INVALID;
            } else {
                ret = HEADER_MAGIC_INVALID;
            }
        } else {
            ret = HEADER_DECRYPT_ERR;
        }

        free(buf);
    } else {
        ret = HEADER_ALLOCATE_BUF_ERR;
    }

    return ret;
}


}
