#include <string.h>
#include "FirmwareData.hh"
#include "DataChunk.hh"
#include "../util/dir.h"

namespace fw {


MSG_CODE FirmwareData::valid(const string &file_name) {
    MSG_CODE ret = MSG_OK;

    FILE *file = fopen(file_name.c_str(), "rb");

    if (nullptr != file) {
        Header header;

        if (!header.valid(file)) {
            ret = FWD_INVALID_HEADER;
        }

        fclose(file);
    } else {
        ret = FWD_ERR_OPEN_FILE;
    }

    return ret;
}


MSG_CODE FirmwareData::extract(const string &file_in, const string &dir_dst, string &file_name_FDAT) {
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
        ret = DataChunk::save(file, dir_dst.c_str(), file_name_FDAT);
    }

    return ret;
}


MSG_CODE FirmwareData::pack(const string &dir_in, const string &file_dst) {
    MSG_CODE ret = MSG_OK;

    // create output file
    FILE *file = fopen(file_dst.c_str(), "wb");

    if (nullptr != file) {
        // write header
        Header header;
        header.write(file);

        // write chunks
        DataChunk::pack(file, dir_in);
    }

    return ret;
}


}
