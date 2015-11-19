#ifndef FWT_HEADER2ND_HH
#define FWT_HEADER2ND_HH


#include "Header.hh"
#include "../crypto/CypherAES.hh"
#include "Header1st.hh"

namespace fw {

#define FDAT_AES_BLOCK_LEN  1024


class Header2nd : public Header1st {
public:
    Header2nd(void) {
        _gen = GEN_2ND;
        _cypher = make_shared<CypherAES>();
    }

    virtual size_t get_blk_len() const {
        return FDAT_AES_BLOCK_LEN;
    }

    virtual unique_ptr<Header> create() override {
        return make_unique<Header2nd>();
    }
};


}


#endif //FWT_HEADER2ND_HH
