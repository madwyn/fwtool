#include <message_inc.h>

#define MSG_ZIP  "zip: "

DEF_MSG(ZIP_FILE_NOT_EXIST,             MSG_ZIP "zip file doesn't exist")
DEF_MSG(ZIP_FILE_INVALID,               MSG_ZIP "zip file is invalid")
DEF_MSG(ZIP_FILE_INFO_INVALID,          MSG_ZIP "zip file global info is invalid")
DEF_MSG(ZIP_FILE_ERR_GET_CUR_INFO,      MSG_ZIP "get file get current file info error")
DEF_MSG(ZIP_FILE_ERR_LOCATE_FIRST,      MSG_ZIP "locate first file in zip error")
DEF_MSG(ZIP_FILE_NOT_READY,             MSG_ZIP "zip file is not ready to use")
DEF_MSG(UNZIP_ERR_WRITE_BUF_TO_FILE,    MSG_ZIP "write buffer to file error")
DEF_MSG(UNZIP_ERR_READ_FILE_TO_BUF,     MSG_ZIP "read file to buffer error")
DEF_MSG(UNZIP_ERR_ALLOCATE_BUF,         MSG_ZIP "allocate buffer error")
DEF_MSG(UNZIP_ERR_CREATE_OUTPUT_FILE,   MSG_ZIP "create output file error")
DEF_MSG(UNZIP_ERR_OPEN_CUR_ZIP_FILE,    MSG_ZIP "open current file in zip error")