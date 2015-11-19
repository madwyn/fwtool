#ifndef FWT_CYPHERAES_HH
#define FWT_CYPHERAES_HH

#include "Cypher.hh"

namespace fw {


class CypherAES : public Cypher {
public:
    MSG_CODE enc  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE dec  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len, int mode);
};


}

#endif //FWT_CYPHERAES_HH
