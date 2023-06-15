#include "pdp.h"

int main() {
    Memory mem = {0};
    memory_load_data(&mem, "data.txt");
    memory_dump(&mem, 0x0200, 0x000c);
    memory_dump(&mem, 0x0040, 0x000c);
    return EXIT_SUCCESS;
}