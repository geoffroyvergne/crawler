#include <getopt.h>
#include <config.h>

#ifndef CLI
#define CLI

static struct option long_options_rest[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"port", required_argument, 0, 'p'},
    {"host", required_argument, 0, 'o'},
    {"target", required_argument, 0, 't'},
    {"config", required_argument, 0, 'c'}
};

static struct option long_options_cli[] = {
    {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"url", required_argument, 0, 'u'}
};

static int version_flag;
void print_usage();
void print_version();
config cli_get_options(int argc, char **argv);

#endif 


