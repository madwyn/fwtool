#ifndef FWT_CMD_H
#define FWT_CMD_H


#include <fwt_def.h>

#define OPT_FULL(OPT, OPT_S) (OPT " " OPT_S)

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define MSG_DESCRIPTION     "fwtool version \"" VERSION "\" 2015"


// option group MODE
#define OPT_GRP_MODE        "grp_mode"

#define OPT_MODE_ADV_HELP   "--advanced_help"
#define OPT_MODE_ADV_HELP_S "-a"
#define OPT_MODE_ADV_HELP_F OPT_FULL(OPT_MODE_ADV_HELP, OPT_MODE_ADV_HELP_S)

#define OPT_MODE_EXTRACT    "--extract"
#define OPT_MODE_EXTRACT_S  "-x"
#define OPT_MODE_EXTRACT_F  OPT_FULL(OPT_MODE_EXTRACT, OPT_MODE_EXTRACT_S)

#define OPT_MODE_CREATE     "--create"
#define OPT_MODE_CREATE_S   "-c"
#define OPT_MODE_CREATE_F   OPT_FULL(OPT_MODE_CREATE, OPT_MODE_CREATE_S)

// option group IO
#define OPT_GRP_IO          "grp_io"

#define OPT_IN              "--input"
#define OPT_IN_S            "-i"
#define OPT_IN_F            OPT_FULL(OPT_IN, OPT_IN_S)
#define OPT_OUT             "--ouput"
#define OPT_OUT_S           "-o"
#define OPT_OUT_F           OPT_FULL(OPT_OUT, OPT_OUT_S)

// option group options
#define OPT_GRP_OPTION      "grp_option"

#define OPT_VERBOSE         "--verbose"
#define OPT_VERBOSE_V       "-v"
#define OPT_VERBOSE_F       OPT_FULL(OPT_VERBOSE, OPT_VERBOSE_V)

#define MSG_MODE_EXTRACT "eXtract firmware.\n" \
            "Extract everything from the firmware updater.\n" \
			"Arguments:\n" \
			"--input, required\n" \
				"\tFirmware updater for Windows (*.exe).\n" \
			"--output, optional\n" \
				"\tThe directory for extracting."

#define MSG_MODE_CREATE "Create firmware.\n" \
            "Rebuild FDAT, encrypt and rebuild FirmwareData.\n" \
			"Arguments:\n" \
			"--input, required\n" \
				"\tThe output directory from extract mode.\n" \
			"--output, optional\n" \
				"\tThe output firmware updater."

#define MSG_MODE_ADV_HELP  "Show advanced help with all possible options and flags with detialed usage."

#define MSG_IO_IN   "For --extract:\tinput file\n" \
				    "For --create:\tinput directory\n"

#define MSG_IO_OUT	"For --extract:\toutput directory\n" \
				    "For --create:\toutput file\n"

#define MSG_OPT_VERBOSE "Verbose output."

#endif //FWT_CMD_H
