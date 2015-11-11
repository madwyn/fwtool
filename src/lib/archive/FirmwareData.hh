//
// Created by madwyn on 06/11/15.
//

#ifndef FWT_FIRMWAREDATA_HH
#define FWT_FIRMWAREDATA_HH


#include <stdint.h>
#include <string>
#include <message_def.h>

namespace fw {


using std::string;


#define FWD_HEADER_MAGIC_LEN    8

/**
 * Data Structure
 *
 * HEADER_MAGIC[8] = {0x89, 0x55, 0x46, 0x55, 0x0D, 0x0A, 0x1A, 0x0A}
 * CHUNKS[] = {}
 *
 *
 *  zip
 *      FirmwareData
 *          FDAT
 *              FDAT_dec
 *                  FirmwareDataRaw.tar
 *
 *
 *
 */

typedef struct {
    uint32_t len;
    uint8_t  type[4];
} DATA_CHUNK_HDR;

class FirmwareData {
public:


    static MSG_CODE extract(const string &file_in, const string &dir_dst);
    static MSG_CODE pack(const string &dir_in, const string &file_dst);

    static MSG_CODE valid(const string &file_name);

    // extract to chunk files

    // pack into FirmwareData

    class Header {
    public:
        static const uint8_t header_magic[FWD_HEADER_MAGIC_LEN];

        static bool valid(const uint8_t *header, const size_t header_len);

        static void write(uint8_t *buf);

        static bool write(FILE *file);
    };

};

}


#endif //FWT_FIRMWAREDATA_HH
