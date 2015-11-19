#ifndef FWT_HEADER_MAGIC_HH
#define FWT_HEADER_MAGIC_HH

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

namespace fw {


class HeaderMagic {
public:
    void init(const uint8_t * const data, size_t len) {
        this->data = data;
        this->len  = len;
    }

    void write(FILE *file) const {
        fwrite(data, 1, len, file);
    }

    bool valid(const uint8_t * const data_in) const {
        return (0 == memcmp(data_in, data, len));
    }

    bool valid(FILE *file) const {
        uint8_t buf[len] = {0};
        bool ret = false;

        long int offset = ftell(file);

        size_t count = fread(buf, 1, len, file);

        if (count == len) {
            ret = valid(buf);
        }

        // rewind file
        fseek(file, offset, SEEK_SET);

        return ret;
    }

    /**
     * skip the header
     */
    bool skip(FILE *file) {
        fseek(file, len, SEEK_CUR);
    }

private:
    const uint8_t *data = nullptr;
    size_t len  = 0;
};


}

#endif //FWT_HEADER_MAGIC_HH
