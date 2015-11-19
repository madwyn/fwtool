#ifndef FWT_CHECKSUM_H
#define FWT_CHECKSUM_H

#include <stdint.h>

#include "endian.h"

/**
 * calculate checksum on little-endian data, take U16, return U16
 */
uint16_t csum_LEU16_U16(const uint8_t * const data, const size_t len) {
    uint16_t csum = 0;
    uint16_t num  = 0;

    for (size_t i = 0; i < len; i += sizeof(uint16_t)) {
        GET_U16_LE(num, (data + i), 0);
        csum += num;
    }

    return csum;
}

#endif //FWT_CHECKSUM_H
