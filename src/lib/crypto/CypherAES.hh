#ifndef FWT_CYPHERAES_HH
#define FWT_CYPHERAES_HH

#include "Cypher.hh"

namespace fw {

#define FDAT_AES_BLOCK_LEN 1024


using std::make_unique;


class CypherAES : public Cypher {
public:
    virtual size_t blk_len() override {return FDAT_AES_BLOCK_LEN;};
    virtual unique_ptr<Cypher> create() override {
        return make_unique<CypherAES>();
    };
    MSG_CODE enc(const uint8_t * const data, const size_t data_len, uint8_t *buf);
    MSG_CODE dec(const uint8_t * const data, const size_t data_len, uint8_t *buf);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len, int mode);
};


}

#endif //FWT_CYPHERAES_HH
