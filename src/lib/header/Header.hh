#ifndef FWT_HEADER_HH
#define FWT_HEADER_HH

#include <memory>
#include <stdint.h>

#include "../crypto/Cypher.hh"
#include "HeaderMagic.hh"
#include "fdata_def.h"


namespace fw{


typedef enum {
    GEN_UNKNOWM = 0,
    GEN_1ST,
    GEN_2ND,
    GEN_3RD
} HDR_GEN;


using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;


class Header {
public:
    shared_ptr<Cypher> cypher = nullptr;
    HDR_GEN            gen    = GEN_UNKNOWM;

    Header(void) {
        gen    = GEN_UNKNOWM;
        cypher = nullptr;
    }

    class Magic : public HeaderMagic {
    public:
        Magic(void) {
            static const uint8_t magic[] = FDAT_IMAGE_MAGIC;
            init(magic, sizeof(magic)-1);
        }
    };

    MSG_CODE valid(const uint8_t *const data, const size_t data_len);

    virtual void _read (const uint8_t *const data) = 0;
    virtual void _write(      uint8_t       *data) const = 0;
    virtual bool _valid(const uint8_t *const data, const size_t data_len) const = 0;
    virtual unique_ptr<Header> create() = 0;
    virtual size_t get_blk_len() const = 0;
};


};


#endif //FWT_HEADER_HH
