#ifndef FWT_FDAT_DEF_H
#define FWT_FDAT_DEF_H

#include <stdint.h>


typedef struct {
    uint16_t csum;      // check sum
    uint16_t len;       // length, also servers as the end flag when len & 0x8000 != 0
} HEADER_U16_CSUM;


#define FDAT_IMAGE_MAGIC            "UDTRFIRM"
#define FDAT_IMAGE_MAGIC_LEN	    (sizeof(FDAT_IMAGE_MAGIC)-1)
#define FDAT_IMAGE_MAGIC_OFFSET     0

// plaintext data in block0 used to guess crypto method

//
//#define	FDAT_IMAGE_BLK0_IDENT_MAGIC		    FDAT_IMAGE_MAGIC
//#define	FDAT_IMAGE_BLK0_IDENT_MAGIC_LEN	    FDAT_IMAGE_MAGIC_LEN
//#define	FDAT_IMAGE_BLK0_IDENT_MAGIC_OFFSET	(sizeof(FDAT_ENC_BLOCK_HDR)+FDAT_IMAGE_MAGIC_OFFSET)


// for 3. gen modified encryption debug version
#define FDAT_IMAGE_HEADER_LEN 0x0200

typedef struct {
    HEADER_U16_CSUM v2;
    uint8_t  magic[FDAT_IMAGE_MAGIC_LEN];   // magic
    uint32_t crc;                           // length, also servers as the end flag when len & 0x8000 != 0
} HEADER_U32_CRC;


#endif //FWT_FDAT_DEF_H
