#include "FDAT.hh"

#include "../crypto/CypherFactory.hh"
#include "../crypto/CypherAES.hh"
#include "../util/file.hh"

namespace fw {


MSG_CODE FDAT::dec(const std::string &file_name_in, const std::string &file_name_dec) {
    MSG_CODE ret = MSG_OK;

    /**
     * the 1st generation firmware uses SHA1
     * the 2nd generation uses AES
     * the 3rd generation has an unknown key
     *
     */
    unique_ptr<Cypher> cypher = CypherFactory::get(file_name_in);

    if (nullptr != cypher) {
        // check the file size matches sector length
        size_t file_size = fs_size(file_name_in);
        size_t sec_len   = cypher->get_sec_len();

        if (0 == (file_size % sec_len)) {
            size_t sec_num = file_size / sec_len;

            FILE *file_in = fopen(file_name_in.c_str(), "rb");

            uint8_t *buf_sec = (uint8_t *)malloc(sec_len);  // read buffer
            uint8_t *buf_dec = (uint8_t *)malloc(sec_len);  // decrypt buffer

            // loop through all sector
            for (size_t i = 0; i < sec_num; ++i) {
                // read a sector
                fread(buf_sec, 1, sec_len, file_in);

                // decrypt it
                ret = cypher->dec(buf_sec, buf_dec, sec_len);

                if (MSG_OK == ret) {
                    printf("%d\n", i);

                    // check sum

                    // write it

                } else {
                    break;
                }
            }
        } else {
            // todo CRYPTO_CYPHER_FILE_SIZE_NOT_MATCH_BLOCK_SIZE
            printf("sector not match\n");
        }

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
