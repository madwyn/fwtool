#ifndef FWT_HEADER3RD_HH
#define FWT_HEADER3RD_HH


#include "Header.hh"
#include "Header2nd.hh"

namespace fw {


class Header3rd : public Header {
public:
    Header3rd() {
        _gen = GEN_3RD;
        _cypher = make_shared<CypherAES>();
    }

    uint32_t _crc;

    virtual void _read(const uint8_t *const data);
    virtual void _write(uint8_t *data) const;
    virtual bool _valid(const uint8_t *const data, const size_t data_len) const ;
    virtual size_t get_blk_len() const override {
        return FDAT_AES_BLOCK_LEN;
    }
    virtual unique_ptr<Header> create() override {
        return make_unique<Header3rd>();
    }
};


}


#endif //FWT_HEADER3RD_HH
