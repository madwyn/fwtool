#include <message_inc.h>

#define MSG_HEADER  "header: "

DEF_MSG(HEADER_MAGIC_INVALID,               MSG_HEADER "magic is invalid")
DEF_MSG(HEADER_DECRYPT_ERR,                 MSG_HEADER "decrypt header error")
DEF_MSG(HEADER_ALLOCATE_BUF_ERR,            MSG_HEADER "allocate decryption buffer error")
DEF_MSG(HEADER_INVALID,                     MSG_HEADER "invalid header data")