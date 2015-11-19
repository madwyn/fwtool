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
     * the 3rd generation has an unknown structure
     */
    unique_ptr<Header> header = HeaderFactory::get(file_name_in);

    if (nullptr != header) {
        if (GEN_3RD != header->_gen) {
            // check the file size matches sector length
            size_t file_size = fs_size(file_name_in);
            size_t blk_len   = header->get_blk_len();

            if (0 == (file_size % blk_len)) {
                size_t sec_num = file_size / blk_len;

                FILE *file_in  = fopen(file_name_in.c_str() , "rb");
                FILE *file_out = fopen(file_name_dec.c_str(), "wb");

                uint8_t *buf_blk = (uint8_t *)malloc(blk_len);  // read buffer
                uint8_t *buf_dec = (uint8_t *)malloc(blk_len);  // decrypt buffer

                // loop through all blocks
                for (size_t i = 0; i < sec_num; ++i) {
                    // read a block
                    fread(buf_blk, 1, blk_len, file_in);

                    // decrypt it
                    ret = header->_cypher->dec(buf_blk, buf_dec, blk_len);

                    if (MSG_OK == ret) {
                        // read header info
                        header->_read(buf_dec);
                        // write content to file
                        fwrite(buf_dec, 1, header->_len_dec, file_out);
                    } else {
                        break;
                    }
                }
            } else {
                ret = FDAT_FILE_SIZE_NOT_MATCH_ENCRYPT_BLOCK_SIZE;
            }
        } else {
            // only first half of first block is encrypted with 2.gen aes key
            // payload of FDAT uses new key and can not be decrypted
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
