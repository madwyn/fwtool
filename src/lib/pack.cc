#include <message_def.h>

#include "pack.h"
#include "archive/ZipFile.hh"

using fw::ZipFile;

static MSG_CODE g_pack_err = MSG_OK;

int
unpack(const char *const file_in, const char *const dir_out) {
    ZipFile zip_file;
    g_pack_err = zip_file.extract(file_in, dir_out);
    return (MSG_OK == g_pack_err);
}

const char *
get_last_err(void) {
    return get_message(g_pack_err);
}
