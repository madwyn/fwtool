#ifndef FWT_CYPHERSHA1_HH
#define FWT_CYPHERSHA1_HH

#include "Cypher.hh"


namespace fw {

#define	FDC_SHA1_BLOCK_LEN	1000


using std::make_unique;


class CypherSHA1: public Cypher {
    virtual size_t blk_len() override {return FDC_SHA1_BLOCK_LEN;};
    virtual unique_ptr<Cypher> create() override {return make_unique<CypherSHA1>();};

    MSG_CODE enc(const uint8_t * const data, const size_t data_len, uint8_t *buf);
    MSG_CODE dec(const uint8_t * const data, const size_t data_len, uint8_t *buf);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len);
};

}


#endif //FWT_CYPHERSHA1_HH
