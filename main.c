#include <stdlib.h>
#include <stdio.h>
#include "pdp.h"

int main() {
    uint16_t var = 1;
    printf("%"PRIu16"\n", var);
    printf("%d\n", is_big_endian());
    printf("%"PRIu16"\n", to_little_endian(var));
    return EXIT_SUCCESS;
}