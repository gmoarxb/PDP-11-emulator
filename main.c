#include <stdlib.h>
#include <getopt.h>
#include "pdp.h"

void do_halt() {
    puts("THE END!!!");
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    char* data_path = argv[argc - 1];
    Pdp11 pdp_11 = {0};
    memory_load_data(&pdp_11.memory, data_path);
    pdp_11.r[7] = 01000;
    while (1) {
        word w = memory_read_word(&pdp_11.memory, pdp_11.r[7]);
        printf("%06"PRIo16" %06"PRIo16"\n", pdp_11.r[7], w);
        pdp_11.r[7] += 2;
        if (w == 0) {
            do_halt();
        }
    }
    return EXIT_SUCCESS;
}

// #define COMMAND_OPTIONS ""

// int main(int argc, char* argv[]) {
//     if (argc <= 1) {
//         log_state(current_log_level, "main", "Need a path to data in command line!");
//     }
//     while (getopt(argc, argv, COMMAND_OPTIONS) != -1) {
//     }
//     char* data_path = argv[argc - 1];
//     Pdp11 pdp_11 = {0};
//     memory_load_data(&pdp_11.memory, data_path);
//     memory_dump(&pdp_11.memory, 0x0200, 0x000c);
//     memory_dump(&pdp_11.memory, 0x0040, 0x000c);
//     return EXIT_SUCCESS;
// }