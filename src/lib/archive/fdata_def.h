#ifndef FWT_FDATA_DEF_H
#define FWT_FDATA_DEF_H

#include <stdint.h>

#define FDAT_IMAGE_MAGIC            "UDTRFIRM"
#define FDAT_IMAGE_MAGIC_LEN	    (sizeof(FDAT_HEADER_MAGIC)-1)
#define FDAT_IMAGE_MAGIC_OFFSET     0

// plaintext data in block0 used to guess crypto method

#define	FDAT_IMAGE_BLK0_IDENT_MAGIC		    FDAT_IMAGE_MAGIC
#define	FDAT_IMAGE_BLK0_IDENT_MAGIC_LEN	    FDAT_IMAGE_MAGIC_LEN
#define	FDAT_IMAGE_BLK0_IDENT_MAGIC_OFFSET	(sizeof(FDAT_ENC_BLOCK_HDR)+FDAT_IMAGE_MAGIC_OFFSET)


typedef struct {
    uint16_t csum;      // check sum
    uint16_t len;       // length, also servers as the end flag when len & 0x8000 != 0
} FDAT_BLOCK_HEADER;

#endif //FWT_FDATA_DEF_H
