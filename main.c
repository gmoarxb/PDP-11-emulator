#include <stdlib.h>
#include <stdio.h>
#include "pdp.h"

int main() {
    uint16_t var = 1;
    printf("%"PRIu16"\n", var);
    printf("%"PRIu16"\n", get_right_endian_word(var));
    return EXIT_SUCCESS;
}