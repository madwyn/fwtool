#ifndef FWT_CYPHER_HH
#define FWT_CYPHER_HH

#include <string>
#include <string.h>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <message_def.h>
#include "../util/print_tool.h"

namespace fw {

using std::string;
using std::unique_ptr;

typedef enum {
    ENC_UNKNOWM = 0,
    ENC_AES,
    ENC_SHA1
} ENC_METHOD;

class Cypher {
public:
    MSG_CODE dec_file(const string &file_name_in, const string &file_name_out);
    MSG_CODE enc_file(const string &file_name_in, const string &file_name_out);

    virtual MSG_CODE enc(const uint8_t * const data, const size_t data_len, uint8_t *buf) = 0;
    virtual MSG_CODE dec(const uint8_t * const data, const size_t data_len, uint8_t *buf) = 0;

    virtual size_t blk_len() = 0;
    virtual unique_ptr<Cypher> create() = 0;

protected:
    static MSG_CODE _crypt_buf(const uint8_t *const input, uint8_t *output, size_t len, size_t buf_len, auto func) {
        MSG_CODE ret = MSG_OK;

        uint8_t *buf_in  = (uint8_t *)malloc(buf_len);
        uint8_t *buf_out = (uint8_t *)malloc(buf_len);

        const uint8_t *in  = input;
              uint8_t *out = output;

        size_t cur_len = buf_len;

        for (size_t remain = len; remain > 0; remain -= cur_len) {
            if (remain < buf_len) {
                cur_len = remain;

                // copy the sort data to a block
                memcpy(buf_in, input + (len - remain), cur_len);
                in  = buf_in;
                out = buf_out;
            }

            // encrypt/dec 16 bit each time
            if (0 != func(in, out)) {
                ret = CRYPTO_CYPHER_AES_CRYPT_ERR;
                break;
            }

            if (remain < buf_len) {
                // copy the out_buf to output
                memcpy(output + (len - remain), buf_out, cur_len);
            }

            in  += cur_len;
            out += cur_len;
        }

        free(buf_in);
        free(buf_out);

        return ret;
    }
};


}

#endif //FWT_CYPHER_HH
