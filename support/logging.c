#include <stdio.h>
#include <stdlib.h>
#include "../pdp.h"

#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

LogLevel current_log_level = LOG_ERROR;

void log_state(LogLevel log_level, const char* const function_name, const char* const message) {
    if (log_level < current_log_level) return;
    switch (current_log_level) {
        case LOG_WARNING: log_warning(message);
        break;
        case LOG_TRACE: log_trace(message);
        break;
        case LOG_DEBUG: log_debug(message);
        break;
        case LOG_INFO: log_info(message);
        break;
        case LOG_ERROR: log_error(function_name, message);
        break;
    }
}

void log_error(const char* const function_name, const char* const message) {
    fprintf(stderr, BOLD RED "ERROR" RESET
                    " in function "
                    BOLD GREEN "%s" RESET
                    ": %s\n",
                    function_name, message);
    exit(EXIT_FAILURE);
}

void log_info(const char* const message) {
    puts(message);
}

void log_debug(const char* const message) {
    puts(message);
}

void log_trace(const char* const message) {
    puts(message);
}

void log_warning(const char* const message) {
    puts(message);
}