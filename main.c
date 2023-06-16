#include <stdlib.h>
#include <getopt.h>
#include "pdp.h"

#define COMMAND_OPTIONS ""

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        log_state(current_log_level, "main", "Need a path to data in command line!");
    }
    while (getopt(argc, argv, COMMAND_OPTIONS) != -1) {
    }
    char* data_path = argv[argc - 1];
    Memory mem = {0};
    memory_load_data(&mem, data_path);
    memory_dump(&mem, 0x0200, 0x000c);
    memory_dump(&mem, 0x0040, 0x000c);
    return EXIT_SUCCESS;
}