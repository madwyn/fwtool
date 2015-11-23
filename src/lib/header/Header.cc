#include "Header.hh"
#include "fdat_def.h"
#include "../archive/UDRFIRM.hh"
#include "../util/print_tool.h"
#include "HeaderImage.hh"


namespace fw {


MSG_CODE Header::valid(const uint8_t *const data_enc, const size_t data_len) {
    MSG_CODE ret     = MSG_OK;
    size_t   buf_len = get_blk_len();
    uint8_t *buf     = (uint8_t *)malloc(buf_len);

    if (nullptr != buf) {
        ret = dec(data_enc, buf, buf_len);

        // decode the message
        if (MSG_OK == ret) {
            assert(nullptr != _payload);
            // verify the decrypted header, the first sector
            HeaderImage headerImage;
            headerImage.read(_payload);

            if (headerImage.valid(_payload, _len_dec)) {
                // validate the FDAT header
                ret = _valid(buf, data_len) ? MSG_OK : HEADER_INVALID;
            } else {
                ret = HEADER_MAGIC_INVALID;
            }
        } else {
            printf("decrypt error: %s\n", gm(ret));
            ret = HEADER_DECRYPT_ERR;
        }

        free(buf);
    } else {
        ret = HEADER_ALLOCATE_BUF_ERR;
    }

    return ret;
}


MSG_CODE Header::dec(const uint8_t *const input, uint8_t *output, const size_t len) {
    MSG_CODE ret = _cypher->dec(input, output, len);

    if (MSG_OK == ret) {
        _read(output);
    }

    return ret;
}


void Header::write(FILE *file) {
    fwrite(_payload, 1, _len_dec, file);
}

}
