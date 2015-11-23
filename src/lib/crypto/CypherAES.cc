#include "CypherAES.hh"
#include "../util/print_tool.h"
#include <mbedtls/aes.h>
#include <string.h>


namespace fw {

#ifndef AES_BLOCK_LEN
#define AES_BLOCK_LEN 16
#endif


MSG_CODE CypherAES::enc(const uint8_t * const input, uint8_t *output, const size_t len) {
    return crypt(input, output, len, MBEDTLS_AES_ENCRYPT);
}


MSG_CODE CypherAES::dec(const uint8_t * const input, uint8_t *output, const size_t len) {
    return crypt(input, output, len, MBEDTLS_AES_DECRYPT);
}


MSG_CODE CypherAES::crypt(const uint8_t *const input, uint8_t *output, const size_t len, int mode) {
    static const uint8_t key[] = {
            0xE3, 0xB0, 0xC4, 0x42, 0x98, 0xFC, 0x1C, 0x14,
            0x9A, 0xFB, 0xF4, 0xC8, 0x99, 0x6F, 0xB9, 0x24,
    };

    MSG_CODE ret = MSG_OK;
    int ret_crypt = 0;

    if (_mode != mode) {
        // set key
        if (MBEDTLS_AES_ENCRYPT == mode) {
            ret_crypt = mbedtls_aes_setkey_enc(&_ctx, key, sizeof(key) * 8);
        } else {
            ret_crypt = mbedtls_aes_setkey_dec(&_ctx, key, sizeof(key) * 8);
        }

        _mode = mode;
    }

    if (0 == ret_crypt) {
        auto _crypt = [this, &mode](const uint8_t *const in, uint8_t *out) {
            return mbedtls_aes_crypt_ecb(&_ctx, mode, in, out);
        };

        ret = _crypt_buf(input, output, len, AES_BLOCK_LEN, _crypt);
    } else {
        ret = CRYPTO_CYPHER_AES_SET_KEY_ERR;
    }

    return ret;
}


}
