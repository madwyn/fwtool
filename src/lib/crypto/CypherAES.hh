#ifndef FWT_CYPHERAES_HH
#define FWT_CYPHERAES_HH

#include "Cypher.hh"

namespace fw {

#define FDAT_AES_SECTOR_LEN 1024


using std::make_unique;


class CypherAES : public Cypher {
public:
    virtual size_t get_sec_len() override {return FDAT_AES_SECTOR_LEN;};
    virtual unique_ptr<Cypher> create() override {
        return make_unique<CypherAES>();
    };
    MSG_CODE enc  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE dec  (const uint8_t * const input, uint8_t *output, const size_t len);
    MSG_CODE crypt(const uint8_t * const input, uint8_t *output, const size_t len, int mode);
};


}

#endif //FWT_CYPHERAES_HH
