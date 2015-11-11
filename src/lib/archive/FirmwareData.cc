#include <string.h>
#include "FirmwareData.hh"
#include "../crypto/Cypher.hh"
#include "../crypto/CypherFactory.hh"
#include "DataChunk.hh"
#include "../util/dir.h"

namespace fw {


MSG_CODE FirmwareData::valid(const string &file_name) {
    MSG_CODE ret = MSG_OK;

    FILE *file = fopen(file_name.c_str(), "rb");

    if (nullptr != file) {
        uint8_t *header = (uint8_t *)malloc(FWD_HEADER_MAGIC_LEN);

        if (nullptr != header) {
            size_t header_len = fread(header, 1, FWD_HEADER_MAGIC_LEN, file);

            if (!Header::valid(header, header_len)) {
                ret = FWD_INVALID_HEADER;
            }

            free(header);
        } else {
            ret = FWD_ERR_ALLOCATE_HEADER_BUF;
        }

        fclose(file);
    } else {
        ret = FWD_ERR_OPEN_FILE;
    }

    return ret;
}



MSG_CODE FirmwareData::extract(const string &file_in, const string &dir_dst) {
    // check validity
    MSG_CODE ret = valid(file_in);

    if (MSG_OK == ret) {
        // create if not exist
        MKDIR(dir_dst.c_str());

        // extract chunks
        FILE *file = fopen(file_in.c_str(), "rb");

        // skip head
        fseek(file, FWD_HEADER_MAGIC_LEN, SEEK_SET);

        // save the chunk to file
        ret = DataChunk::save(file, dir_dst.c_str());
    }

    return ret;
}

const uint8_t FirmwareData::Header::header_magic[FWD_HEADER_MAGIC_LEN] = {
        0x89, 0x55, 0x46, 0x55, 0x0d, 0x0a, 0x1a, 0x0a
};

bool FirmwareData::Header::valid(const uint8_t *header, const size_t header_len) {
    if (FWD_HEADER_MAGIC_LEN == header_len) {
        return (0 == memcmp(header, header_magic, FWD_HEADER_MAGIC_LEN));
    }

    return false;
}

void FirmwareData::Header::write(uint8_t *buf) {
    memcpy(buf, header_magic, FWD_HEADER_MAGIC_LEN);
}

bool FirmwareData::Header::write(FILE *file) {
    return (FWD_HEADER_MAGIC_LEN == fwrite(header_magic, FWD_HEADER_MAGIC_LEN, 1, file));
}

MSG_CODE FirmwareData::pack(const string &dir_in, const string &file_dst) {
    MSG_CODE ret = MSG_OK;

    // create output file
    FILE *file = fopen(file_dst.c_str(), "wb");

    if (nullptr != file) {
        // write header
        Header::write(file);

        // write chunks
        DataChunk::pack(file, dir_in);
    }

    return ret;
}


}
