#include <cargo.h>
#include <stdlib.h>

#include "cmd.h"
#include <pack.h>

int
main(int argc, char **argv) {

    int ret = 0;

    // working mode
    int extract  = 0;
    int create   = 0;
    int adv_help = 0;

    // other options
    char *input  = malloc(512);
    char *output = malloc(512);

    int v_major = 0;
    int v_minor = 0;
    int level   = 0;
    int verbose = 0;

    // flag context
    cargo_t cargo;

    if (cargo_init(&cargo, 0, "%s", argv[0])) {
        fprintf(stderr, "Failed to init command line parsing\n");
        return -1;
    }

    cargo_set_description(cargo, MSG_DESCRIPTION);

    // working mode group
    ret |= cargo_add_mutex_group(cargo, CARGO_MUTEXGRP_ONE_REQUIRED, OPT_GRP_MODE, "Working Mode", "The working mode");

    ret |= cargo_add_option(cargo, 0, OPT_MODE_ADV_HELP_F, MSG_MODE_ADV_HELP, "b", &adv_help);
    ret |= cargo_add_option(cargo, 0, OPT_MODE_EXTRACT_F, MSG_MODE_EXTRACT,  "b", &extract);
    ret |= cargo_add_option(cargo, 0, OPT_MODE_CREATE_F, MSG_MODE_CREATE,   "b", &create);

    ret |= cargo_mutex_group_add_option(cargo, OPT_GRP_MODE, OPT_MODE_ADV_HELP);
    ret |= cargo_mutex_group_add_option(cargo, OPT_GRP_MODE, OPT_MODE_EXTRACT);
    ret |= cargo_mutex_group_add_option(cargo, OPT_GRP_MODE, OPT_MODE_CREATE);

    // input parameters
    ret |= cargo_add_group(cargo, 0, OPT_GRP_IO, "Input and output parameters", "They have different meanings depending on working mode.");

    ret |= cargo_add_option(cargo, 0, OPT_IN_F,  MSG_IO_IN,  "s", &input);
    ret |= cargo_add_option(cargo, 0, OPT_OUT_F, MSG_IO_OUT, "s", &output);

    ret |= cargo_group_add_option(cargo, OPT_GRP_IO, OPT_IN);
    ret |= cargo_group_add_option(cargo, OPT_GRP_IO, OPT_OUT);

    // optional parameters
    ret |= cargo_add_group(cargo, CARGO_GROUP_HIDE, OPT_GRP_OPTION, "Optional", "These are optional.");

    ret |= cargo_add_option(cargo, 0, OPT_VERBOSE_F, MSG_OPT_VERBOSE, "b", &verbose);

    ret |= cargo_group_add_option(cargo, OPT_GRP_OPTION, OPT_VERBOSE);

    if (!cargo_parse(cargo, 0, 1, argc, argv)) {
        if (adv_help) {
            // Remove the group hide flag so it shows up in the usage.
            cargo_group_set_flags(cargo, OPT_GRP_OPTION, 0);
            cargo_print_usage(cargo, CARGO_USAGE_FULL);
        } else if (extract) {
            // implement extract
            if (!unpack(input, output)) {
                printf("%s\n", get_last_err());
            }
        } else if (create) {
            // implement create
        }
    }

    cargo_destroy(&cargo);

    return ret;
}
