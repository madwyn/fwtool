#ifndef FWT_CYPHERSHA1_HH
#define FWT_CYPHERSHA1_HH

#include "Cypher.hh"


namespace fw {

#define	FDC_SHA1_SECTOR_LEN	1000


using std::make_unique;


class CypherSHA1: public Cypher {
    virtual size_t get_sec_len() override {return FDC_SHA1_SECTOR_LEN;};
    virtual unique_ptr<Cypher> create() override {return make_unique<CypherSHA1>();};

    MSG_CODE enc  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE dec  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len);
};

}


#endif //FWT_CYPHERSHA1_HH
