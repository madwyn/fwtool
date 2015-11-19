#include <message_def.h>

#include <string>

#include "pack.h"
#include "archive/ZipFile.hh"
#include "archive/FirmwareData.hh"
#include "archive/FDAT.hh"


using std::string;

using fw::ZipFile;
using fw::FirmwareData;
using fw::FDAT;


static MSG_CODE g_pack_err = MSG_OK;

#define DIR_FWD_OUTPUT  "FirmwareData"

int
unpack(const char *const file_in, const char *const dir_out) {
    ZipFile zip_file;

    // search the firmware data first
    string file_name_fwd = "";

    g_pack_err = ZipFile::valid(file_in);

    // input is the zip file
    if (MSG_OK == g_pack_err) {
        printf("input file is ZIP\n");
        g_pack_err = zip_file.extract(file_in, dir_out, file_name_fwd);
    } else {
        g_pack_err = FirmwareData::valid(file_in);

        if (MSG_OK == g_pack_err) {
            printf("input file is FirmwareData\n");
            file_name_fwd = file_in;
        }
    }

    if (MSG_OK == g_pack_err) {
        printf("FirmwareData: %s\n", file_name_fwd.c_str());

        g_pack_err = FirmwareData::valid(file_name_fwd);

        if (MSG_OK == g_pack_err) {
            printf("FirmwareData is valid\n");

            string dir_fwd_out = string(dir_out) + "/" + DIR_FWD_OUTPUT;
            string file_name_FDAT = "";

            g_pack_err = FirmwareData::extract(file_name_fwd, dir_fwd_out, file_name_FDAT);

            if (MSG_OK == g_pack_err) {
                printf("FDAT: %s\n", file_name_FDAT.c_str());

                string file_name_FDAT_dec = file_name_FDAT + ".dec";

                g_pack_err = fw::FDAT::dec(file_name_FDAT, file_name_FDAT_dec);

                if (MSG_OK == g_pack_err) {
                    // extract the FDAT image

                    // keep header somewhere for repacking

                    // extract tar
                }
            }
        }
    }

    return (MSG_OK == g_pack_err);
}


int pack(const char *const dir_input, const char *const file_output) {
    g_pack_err = FirmwareData::pack(dir_input, file_output);

    return (MSG_OK == g_pack_err);
}


const char *
get_last_err(void) {
    return get_message(g_pack_err);
}
