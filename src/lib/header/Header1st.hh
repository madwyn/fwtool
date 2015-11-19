#ifndef FWT_HEADER1ST_HH
#define FWT_HEADER1ST_HH


#include "Header.hh"
#include "../crypto/CypherSHA1.hh"

namespace fw {

using std::make_shared;

#define	FDC_SHA1_BLOCK_LEN  1000


class Header1st : public Header {
public:
    Header1st(void) {
        gen    = GEN_1ST;
        cypher = make_shared<CypherSHA1>();
    }

    uint16_t _csum;
    uint16_t _len;
    uint16_t _len_dec;

    virtual void _read(const uint8_t *const data);
    virtual void _write(uint8_t *data) const;
    virtual bool _valid(const uint8_t *const data, const size_t data_len) const;

    virtual size_t get_blk_len() const {
        return FDC_SHA1_BLOCK_LEN;
    }

    virtual unique_ptr<Header> create() override {
        return make_unique<Header1st>();
    }
};


}


#endif //FWT_HEADER1ST_HH
