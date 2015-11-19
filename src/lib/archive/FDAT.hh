#ifndef FWT_FDAT_HH
#define FWT_FDAT_HH


#include <message_def.h>

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdint.h>
#include "../header/HeaderMagic.hh"
#include "../header/fdata_def.h"
#include "../util/print_tool.h"


namespace fw {

using std::string;


class FDAT {
public:
    static MSG_CODE dec(const string &file_name_in, const string &file_name_dec);
    static MSG_CODE enc(const string &file_name_in, const string &file_name_enc);

    class Magic : public HeaderMagic {
    public:
        Magic(void) {
            static const uint8_t magic[] = FDAT_IMAGE_MAGIC;
            init(magic, FDAT_IMAGE_MAGIC_LEN);
        }
    };

    static bool valid(const uint8_t * const data_dec) {
        Magic magic;
        return magic.valid(data_dec + sizeof(HEADER_U16_CSUM));
    }
};


}


#endif //FWT_FDAT_HH
