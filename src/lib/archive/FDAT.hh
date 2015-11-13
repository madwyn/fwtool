#ifndef FWT_FDAT_HH
#define FWT_FDAT_HH


#include <message_def.h>

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdint.h>
#include "HeaderMagic.hh"
#include "fdata_def.h"


namespace fw {

using std::string;


class FDAT {
public:
    static MSG_CODE dec(const string &file_name_in, const string &file_name_dec);
    static MSG_CODE enc(const string &file_name_in, const string &file_name_enc);

    class Header : public HeaderMagic {
    public:
        Header(void) {
            static const uint8_t header[] = "UDTRFIRM";
            init(header, sizeof(header)-1);
        }
    };

    static bool valid(const uint8_t * const data_dec) {
        Header header;
        return header.valid(data_dec + sizeof(FDAT_BLOCK_HEADER));
    }
};


}


#endif //FWT_FDAT_HH
