#ifndef FWT_PRINT_TOOL_H
#define FWT_PRINT_TOOL_H

#include <stdio.h>
#include <stdint.h>

inline void p_range(const uint8_t *data, const size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02X-", data[i]);
    }

    printf("\n");
}

#endif //FWT_PRINT_TOOL_H
