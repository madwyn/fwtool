#ifndef FWT_CYPHERSHA1_HH
#define FWT_CYPHERSHA1_HH

#include "Cypher.hh"


namespace fw {


class CypherSHA1: public Cypher {
    MSG_CODE enc  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE dec  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len);
};


}


#endif //FWT_CYPHERSHA1_HH
