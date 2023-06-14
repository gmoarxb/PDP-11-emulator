#include <stdlib.h>
#include <stdio.h>
#include "pdp.h"

int main() {
    uint16_t var = 1;
    printf("%"PRIu16" %"PRIu16"\n", var, htons(var));
    printf("%d\n", is_big_endian());
    return EXIT_SUCCESS;
}