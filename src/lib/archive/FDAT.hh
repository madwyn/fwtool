#ifndef FWT_FDAT_HH
#define FWT_FDAT_HH


#include <message_def.h>

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdint.h>
#include "../header/HeaderMagic.hh"
#include "../util/print_tool.h"


namespace fw {

using std::string;


class FDAT {
public:
    static MSG_CODE dec(const string &file_name_in, const string &file_name_dec);
    static MSG_CODE enc(const string &file_name_in, const string &file_name_enc);
};


}


#endif //FWT_FDAT_HH
