#include <message_inc.h>

#define MSG_FDAT  "fdat: "

DEF_MSG(FDAT_FILE_SIZE_NOT_MATCH_ENCRYPT_BLOCK_SIZE,   MSG_FDAT "file size does not match the encrypt block size")
DEF_MSG(FDAT_3RD_GEN_FIRMWARE_NOT_SUPPORTED,           MSG_FDAT "3rd generation firmware is not supported yet")
DEF_MSG(FDAT_CANNOT_DETECT_CYPHER,                     MSG_FDAT "cannot detect the cypher used in the firmware")