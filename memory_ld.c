#include "pdp.h"

#define LINE_MAX_SIZE (0x1 << 0x4)

void memory_load_data() {
    char line[LINE_MAX_SIZE] = {0};
    while (feof(stdin) == false) {
        memset(line, 0, LINE_MAX_SIZE);
        fgets(line, LINE_MAX_SIZE, stdin);
        if (ferror(stdin) == true) {
            error("memory_load_data", "ferror(FILE) is true!");
        }
    }
}