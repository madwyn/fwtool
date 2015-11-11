#include "DataChunk.hh"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "../util/endian.h"
#include "../util/file.hh"


namespace fw {



void DataChunk::Header::read(const uint8_t * const data) {
    len  = read_u32_be(data);   // the first 4 bytes is the length, BIG-endian
    type = CHUNK_NAME_TO_TYPE((char *)data + 4);    // read type
}

void DataChunk::Header::read(FILE *file) {
    HEADER header;
    fread(&header, sizeof(header), 1, file);
    return read((const uint8_t * const) &header);
}


void DataChunk::Header::write(uint8_t *data) {
    write_u32_be(data, len);
    memcpy(data + sizeof(len), CHUNK_STRINGS[type], strlen(CHUNK_STRINGS[type]));
}

void DataChunk::Header::write(FILE *file) {
    HEADER header;
    write((uint8_t *)&header);
    fwrite(&header, sizeof(HEADER), 1, file);
}


MSG_CODE DataChunk::save(FILE *file, const string &dir_dst) {
    MSG_CODE ret = MSG_OK;

    Header header;

    int i = 0;

    while (!feof(file)) {
        header.read(file);

        // output format  dir/n.XXXX.bin
        string file_name_out = dir_dst + "/" + std::to_string(i++) + "." + CHUNK_STRINGS[header.type] + ".bin";

        if (!fs_save_to(file, header.len, file_name_out.c_str())) {
            ret = CHUNK_SAVE_TO_FILE_ERR;
            break;
        }
    }

    return ret;
}


MSG_CODE DataChunk::pack(FILE *file, const string &dir_src) {
    MSG_CODE ret = MSG_OK;
    DIR     *dir = opendir(dir_src.c_str());

    if (nullptr != dir) {
        Header header;

        // sort the list
        dirent **list = fs_ls_sort(dir);

        // get dir item count
        size_t count = fs_ls_count(dir);

        for (int i = 0 ; i < count ; ++i) {
            if (DT_REG == list[i]->d_type) {
                // create header
                header.len  = (uint32_t)fs_size(dir_src + "/" + list[i]->d_name);
                header.type = FILE_NAME_TO_TYPE(list[i]->d_name);

                // write header
                header.write(file);

                // write content
                if (!fs_append_to((dir_src + "/" + list[i]->d_name).c_str(), file)) {
                    ret = CHUNK_APPEND_CONTENT_TO_FILE_ERR;
                    break;
                }
            }
        }

        free(list);

        closedir(dir);
    } else {
        ret = CHUNK_OPEN_DIR_ERR;
    }

    return ret;
}


}