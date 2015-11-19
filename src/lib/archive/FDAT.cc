#include <zlib.h>
#include "FDAT.hh"

#include "../crypto/CypherAES.hh"
#include "../util/file.hh"
#include "../header/Header.hh"
#include "../header/HeaderFactory.hh"

namespace fw {


MSG_CODE FDAT::dec(const std::string &file_name_in, const std::string &file_name_dec) {
    MSG_CODE ret = MSG_OK;

    /**
     * the 1st generation firmware uses SHA1
     * the 2nd generation uses AES
     * the 3rd generation has an unknown key
     *
     */
    unique_ptr<Header> header = HeaderFactory::get(file_name_in);

    if (nullptr != header) {
        if (GEN_3RD != header->gen) {

            // check the file size matches sector length
            size_t file_size = fs_size(file_name_in);
            size_t blk_len   = header->get_blk_len();

            if (0 == (file_size % blk_len)) {
                size_t sec_num = file_size / blk_len;

                FILE *file_in  = fopen(file_name_in.c_str() , "rb");
                FILE *file_out = fopen(file_name_dec.c_str(), "wb");

                uint8_t *buf_sec = (uint8_t *)malloc(blk_len);  // read buffer
                uint8_t *buf_dec = (uint8_t *)malloc(blk_len);  // decrypt buffer

                // loop through all blocks
                for (size_t i = 0; i < 1; ++i) {
                    // read a sector
                    fread(buf_sec, 1, blk_len, file_in);

                    // decrypt it
                    ret = header->cypher->dec(buf_sec, buf_dec, blk_len);

                    if (MSG_OK == ret) {

                        // write it

                    } else {
                        break;
                    }
                }
            } else {
                ret = FDAT_FILE_SIZE_NOT_MATCH_ENCRYPT_BLOCK_SIZE;
            }
        } else {
            ret = FDAT_3RD_GEN_FIRMWARE_NOT_SUPPORTED;
        }
    } else {
        ret = FDAT_CANNOT_DETECT_CYPHER;
    }

    return ret;
}


MSG_CODE FDAT::enc(const std::string &file_name_in, const std::string &file_name_enc) {
    MSG_CODE ret = MSG_OK;

    return ret;
}

}
