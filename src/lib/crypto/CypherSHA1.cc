#include "CypherSHA1.hh"

#include <mbedtls/sha1.h>

namespace fw {


#ifndef SHA1_DIGEST_LEN
#define SHA1_DIGEST_LEN	20
#endif

MSG_CODE CypherSHA1::enc(const uint8_t *const data, const size_t data_len, uint8_t *buf) {
    return crypt(data, buf, data_len);
}

MSG_CODE CypherSHA1::dec(const uint8_t *const data, const size_t data_len, uint8_t *buf) {
    return crypt(data, buf, data_len);
}

MSG_CODE CypherSHA1::crypt(const uint8_t *const input, uint8_t *output, const size_t len) {
    static const uint8_t seed_1[SHA1_DIGEST_LEN] = {
            0x8D, 0xE5, 0xA8, 0x56, 0xD2, 0xEE, 0x76, 0xE0,
            0x6C, 0x45, 0xDD, 0x9F, 0x57, 0x12, 0xC6, 0x3A,
            0x0A, 0xDB, 0x05, 0xC1
    };

    static const uint8_t seed_2[SHA1_DIGEST_LEN] = {
            0xAF, 0x80, 0x8F, 0xC3, 0x97, 0x7B, 0x21, 0x87,
            0x75, 0x22, 0x69, 0xDE, 0x83, 0xCC, 0xA6, 0xC6,
            0x12, 0xF0, 0xDC, 0x49
    };

    mbedtls_sha1_context ctx;

    // set key
    mbedtls_sha1_starts(&ctx);
    mbedtls_sha1_update(&ctx, seed_1, SHA1_DIGEST_LEN);
    mbedtls_sha1_update(&ctx, seed_2, SHA1_DIGEST_LEN);

    auto _crypt = [&ctx](const uint8_t *const in, uint8_t *out) {
        // get the latest sha-1 digest (result used to xor data buffer)
        mbedtls_sha1_finish(&ctx, out);

        // use the newly calculated digest, along with "Decrypt_sha1_seed_2"
        // to start a new sha-1 calculation (resulting digest will be used
        // next time through this loop)
        mbedtls_sha1_starts(&ctx);
        mbedtls_sha1_update(&ctx, out   , SHA1_DIGEST_LEN);
        mbedtls_sha1_update(&ctx, seed_2, SHA1_DIGEST_LEN);

        const uint8_t *p_in = in;

        // now take the sha-1 digest (from above) and xor that into
        // the next 20 bytes of the data buffer
        for (size_t i = 0; i < SHA1_DIGEST_LEN; i++) {
            *out++ = (*p_in++ ^ out[i]);
        }

        return 1;
    };

    return _crypt_buf(input, output, len, SHA1_DIGEST_LEN, _crypt);
}


}
