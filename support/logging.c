#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../pdp.h"

#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

LogLevel current_log_level = LOG_ERROR;

void log_state(LogLevel log_level, const char* const message, ...) {
    if (log_level < current_log_level) {
        return;
    }
    log_level_print(log_level);

    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);

    printf("%s", "\n");
    if (log_level == LOG_ERROR) {
        exit(EXIT_FAILURE);
    }
}

void log_level_print(LogLevel log_level) {
    switch (log_level) {
        case LOG_ERROR:
            printf(BOLD RED "ERROR: " RESET);
            break;
        case LOG_INFO:
            printf(BOLD RED "INFO: " RESET);
            break;
        case LOG_DEBUG:
            printf(BOLD RED "DEBUG: " RESET);
            break;
        case LOG_TRACE:
            printf(BOLD RED "TRACE: " RESET);
            break;
        case LOG_WARNING:
            printf(BOLD RED "WARNING: " RESET);
            break;
    }
}