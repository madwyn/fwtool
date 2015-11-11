#ifndef FWT_DATACHUNK_HH
#define FWT_DATACHUNK_HH

#include <string>
#include <stdint.h>
#include <message_def.h>
#include <stdio.h>

#include "../type/chunk_type.h"

namespace fw {

using std::string;


#define DATA_CHUNK_FILE_LIST    "DataChunkFileList.txt"

class DataChunk {
public:
    class Header {
    public:
        typedef struct {
            uint8_t len[4];     // a 32-bit "record length" value (stored BIG-endian!)
            uint8_t type[4];    // 4-character "record type" identifier
        } HEADER;

        uint32_t   len;
        CHUNK_TYPE type;

        void read(FILE *file);
        void read(const uint8_t * const data);

        void write(FILE *file);
        void write(uint8_t *data);
    };

    static MSG_CODE save(FILE *file, const string &dir_dst);
    static MSG_CODE pack(FILE *file, const string &dir_src);

    uint8_t *payload = nullptr;
};

}


#endif //FWT_DATACHUNK_HH
