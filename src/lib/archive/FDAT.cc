#include "FDAT.hh"

#include "../crypto/CypherFactory.hh"
#include "../crypto/CypherAES.hh"

namespace fw {


MSG_CODE FDAT::dec(const std::string &file_name_in, const std::string &file_name_dec) {
    MSG_CODE ret = MSG_OK;

    unique_ptr<Cypher> cypher = CypherFactory::get(file_name_in);

    if (nullptr != cypher) {
        // decrypt file
        cypher->dec_file(file_name_in, file_name_dec);

    } else {
        // todo FDAT_DETECT_CYPHER_ERR

        printf("cannot get cypher");
    }


    return ret;
}


MSG_CODE FDAT::enc(const std::string &file_name_in, const std::string &file_name_enc) {
    MSG_CODE ret = MSG_OK;

    return ret;
}

}
