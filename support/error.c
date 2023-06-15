#include <stdio.h>
#include <stdlib.h>

#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void error(char* function_name, char* message) {
    fprintf(stderr, BOLD RED "ERROR" RESET
                    " in function "
                    BOLD GREEN "%s" RESET
                    ": %s\n",
                    function_name, message);
    exit(EXIT_FAILURE);
}