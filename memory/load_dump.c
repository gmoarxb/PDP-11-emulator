#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <inttypes.h>
#include "../pdp.h"

void memory_load_data(Memory* memory, const char* file_name) {
    FILE* data = fopen(file_name, "r");
    if (!data || ferror(data)) {
        log_state(current_log_level, "memory_load_data", "Unable to open file!");
    }
    if (feof(data)) {
        log_state(current_log_level, "memory_load_data", "Opened file is empty!");
    }
    address block = 0;
    uint16_t size = 0;
    while (!feof(data)) {
        if (fscanf(data, "%4"SCNx16"%4"SCNx16, &block, &size) != 2) {
            log_state(current_log_level, "memory_write_block", "Wrong data file format!");
        }
        memory_write_block(memory, block, size, data);
        char sym = fgetc(data);
        if (sym != '\n' && sym != EOF) {
            log_state(current_log_level, "memory_load_data", "Wrong data file format!");
        }
        while (isspace(sym)) {
            sym = fgetc(data);
        }
        ungetc(sym, data);
    }
    fclose(data);
}

void memory_write_block(Memory* memory, address block, uint16_t size, FILE* data) {
    uint16_t i = 0;
    for (; i < size && (block + i) < MEMORY_SIZE_IN_BYTES; ++i) {
        if (fgetc(data) != '\n') {
            log_state(current_log_level, "memory_write_block", "Wrong data file format!");
        }
        byte value = 0;
        if (fscanf(data, "%2"SCNx8, &value) != 1) {
            log_state(current_log_level, "memory_write_block", "Wrong data file format!");
        }
        memory_write_byte(memory, block + i, value);
    }
    if (i != size) {
        log_state(current_log_level, "memory_write_block", "Writing block size is out of memory size!");
    }
}

void memory_dump(Memory* memory, address block, uint16_t size) {
    if (word_is_address_odd(block)) {
        log_state(current_log_level, "memory_dump", "Block address is not even!");
    } else if (word_is_address_odd(size)) {
        log_state(current_log_level, "memory_dump", "Block size is not even!");
    }
    uint16_t i = 0;
    for (; i < size && (block + i) < MEMORY_SIZE_IN_BYTES; i += 2) {
        uint16_t value = memory_read_word(memory, block + i);
        printf("%06"PRIo16": %06"PRIo16" %04"PRIx16"\n", block + i, value, value);
    }
    if (i != size) {
        log_state(current_log_level, "memory_dump", "Dump block size is out of memory size!");
    }
}