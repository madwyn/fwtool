#ifndef FWT_ENDIAN_H
#define FWT_ENDIAN_H

#include <stdint.h>

// read a 32-bit little-endian unsigned integer
uint32_t read_u32_le(const uint8_t *b) {
    return static_cast<uint32_t>(
            (b[0])      |
            (b[1] << 8) |
            (b[2] << 16)|
            (b[3] << 24) );
}

// read a 32-bit BIG-endian unsigned integer
uint32_t read_u32_be(const uint8_t *b) {
    return static_cast<int32_t>(
            (b[3])      |
            (b[2] << 8) |
            (b[1] << 16)|
            (b[0] << 24) );
}

// read a 16-bit little-endian unsigned integer
uint32_t read_u16_le(const uint8_t *b) {
    return static_cast<uint32_t>(
            (b[0])      |
            (b[1] << 8) |
            (b[2] << 16)|
            (b[3] << 24) );
}

// read a 16-bit BIG-endian unsigned integer
uint32_t read_u16_be(const uint8_t *b) {
    return static_cast<int32_t>(
            (b[3])      |
            (b[2] << 8) |
            (b[1] << 16)|
            (b[0] << 24) );
}

// write 32 bit le, be
void write_u32_be(uint8_t *b, const uint32_t val) {
    b[3] = (uint8_t) ((val & 0x000000FF));
    b[2] = (uint8_t) ((val & 0x0000FF00) >> 8);
    b[1] = (uint8_t) ((val & 0x00FF0000) >> 16);
    b[0] = (uint8_t) ((val & 0xFF000000) >> 24);
}

#endif //FWT_ENDIAN_H
