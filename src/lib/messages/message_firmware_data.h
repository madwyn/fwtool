#include <message_inc.h>

#define MSG_FWD  "fwd: "

DEF_MSG(FWD_ERR_OPEN_FILE,              MSG_FWD "open FirmwareData file error")
DEF_MSG(FWD_ERR_ALLOCATE_HEADER_BUF,    MSG_FWD "allocate header buffer error")
DEF_MSG(FWD_INVALID_HEADER,             MSG_FWD "the input file has an invalid header")
