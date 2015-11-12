#ifndef FWT_ENDIAN_H
#define FWT_ENDIAN_H

#include <stdint.h>


#ifndef PUT_U16_LE
#define PUT_U16_LE(n, b, i)                             \
{                                                       \
    (b)[(i)    ] = (uint8_t) ( (n)       );             \
    (b)[(i) + 1] = (uint8_t) ( (n) >>  8 );             \
}
#endif


#ifndef GET_U16_LE
#define GET_U16_LE(n, b, i)                             \
{                                                       \
    (n) = ( (uint16_t) (b)[(i)    ]       )             \
        | ( (uint16_t) (b)[(i) + 1] <<  8 );            \
}
#endif


#ifndef PUT_U16_BE
#define PUT_U16_BE(n, b, i)                             \
{                                                       \
    (b)[(i) + 1] = (uint8_t) ( (n)       );             \
    (b)[(i)    ] = (uint8_t) ( (n) >>  8 );             \
}
#endif


#ifndef GET_U16_LE
#define GET_U16_LE(n, b, i)                             \
{                                                       \
    (n) = ( (uint16_t) (b)[(i) + 1]       )             \
        | ( (uint16_t) (b)[(i)    ] <<  8 );            \
}
#endif



#ifndef PUT_U32_LE
#define PUT_U32_LE(n, b, i)                             \
{                                                       \
    (b)[(i)    ] = (uint8_t) ( (n)       );             \
    (b)[(i) + 1] = (uint8_t) ( (n) >>  8 );             \
    (b)[(i) + 2] = (uint8_t) ( (n) >> 16 );             \
    (b)[(i) + 3] = (uint8_t) ( (n) >> 24 );             \
}
#endif


#ifndef GET_U32_LE
#define GET_U32_LE(n, b, i)                             \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ]       )             \
        | ( (uint32_t) (b)[(i) + 1] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 2] << 16 )             \
        | ( (uint32_t) (b)[(i) + 3] << 24 );            \
}
#endif


#ifndef PUT_U32_BE
#define PUT_U32_BE(n, b, i)                             \
{                                                       \
    (b)[(i) + 3] = (uint8_t) ( (n)       );             \
    (b)[(i) + 2] = (uint8_t) ( (n) >>  8 );             \
    (b)[(i) + 1] = (uint8_t) ( (n) >> 16 );             \
    (b)[(i)    ] = (uint8_t) ( (n) >> 24 );             \
}
#endif


#ifndef GET_U32_BE
#define GET_U32_BE(n, b, i)                             \
{                                                       \
    (n) = ( (uint32_t) (b)[(i) + 3]       )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i)    ] << 24 );            \
}
#endif


#endif //FWT_ENDIAN_H
