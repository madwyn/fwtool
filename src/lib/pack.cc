#include <message_def.h>

#include <string>

#include "pack.h"
#include "archive/ZipFile.hh"

using std::string;
using fw::ZipFile;


static MSG_CODE g_pack_err = MSG_OK;

int
unpack(const char *const file_in, const char *const dir_out) {
    ZipFile zip_file;

    // search the firmware data first
    string file_name_fwd = "";

    g_pack_err = zip_file.extract(file_in, dir_out, file_name_fwd);

    if (MSG_OK == g_pack_err) {
        printf("%s\n", file_name_fwd.c_str());
    }

    return (MSG_OK == g_pack_err);
}

const char *
get_last_err(void) {
    return get_message(g_pack_err);
}
