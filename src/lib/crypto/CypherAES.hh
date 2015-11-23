#ifndef FWT_CYPHERAES_HH
#define FWT_CYPHERAES_HH

#include <mbedtls/aes.h>
#include "Cypher.hh"

namespace fw {


class CypherAES : public Cypher {
public:
    MSG_CODE enc  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE dec  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len, int mode);
private:
    int _mode = 999;
    mbedtls_aes_context _ctx;
};


}

#endif //FWT_CYPHERAES_HH
