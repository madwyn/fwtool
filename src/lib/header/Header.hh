#ifndef FWT_HEADER_HH
#define FWT_HEADER_HH

#include <memory>
#include <stdint.h>

#include "../crypto/Cypher.hh"
#include "HeaderMagic.hh"
#include "fdat_def.h"


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
    shared_ptr<Cypher> _cypher  = nullptr;
    HDR_GEN            _gen     = GEN_UNKNOWM;
    size_t             _len_dec = 0;
    uint8_t           *_payload = nullptr;

    Header(void) {
        _gen     = GEN_UNKNOWM;
        _cypher  = nullptr;
        _len_dec = 0;
        _payload = nullptr;
    }

    MSG_CODE valid(const uint8_t *const data, const size_t data_len);
    MSG_CODE dec  (const uint8_t *const input, uint8_t *output, const size_t len);

    void write(FILE *file);

    virtual void _read (const uint8_t *const data) = 0;
    virtual void _write(      uint8_t       *data) const = 0;
    virtual bool _valid(const uint8_t *const data, const size_t data_len) const = 0;
    virtual unique_ptr<Header> create() = 0;
    virtual size_t get_blk_len() const  = 0;
};


};


#endif //FWT_HEADER_HH
