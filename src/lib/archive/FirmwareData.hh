#ifndef FWT_FIRMWAREDATA_HH
#define FWT_FIRMWAREDATA_HH


#include <stdint.h>
#include <string>
#include <message_def.h>
#include "../header/HeaderMagic.hh"

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
    static MSG_CODE extract(const string &file_in, const string &dir_dst, string &file_name_FDAT);
    static MSG_CODE pack(const string &dir_in, const string &file_dst);
    static MSG_CODE valid(const string &file_name);

    class Header : public HeaderMagic {
    public:
        Header() {
            static const uint8_t header[] = {0x89, 0x55, 0x46, 0x55, 0x0d, 0x0a, 0x1a, 0x0a};
            init(header, sizeof(header));
        }
    };

};

}


#endif //FWT_FIRMWAREDATA_HH
