#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#include "../pdp.h"

#define FOUR_HEX_SYMBOLS 4
#define TWO_HEX_SYMBOLS 2

typedef struct block_info {
    // "00a2 a23b" and \0 so 4 * 2 + 2
    char address_and_size[FOUR_HEX_SYMBOLS * 2 + 2]; 
    char address_str[FOUR_HEX_SYMBOLS + 1];
    char size_str[FOUR_HEX_SYMBOLS + 1];
    address address_num;
    uint16_t size_num;
} BlockInfo;

void memory_write_block(Memory* memory, FILE* data);
void block_info_process(BlockInfo* block_info);

void memory_load_data(Memory* memory, const char* file_name) {
    FILE* data = fopen(file_name, "r");
    if (!data || ferror(data)) {
        error("memory_load_data", "Unable to open file!");
    }
    if (feof(data)) {
        error("memory_load_data", "Opened file is empty!");
    }
    while (!feof(data)) {
        memory_write_block(memory, data);
    }
}

void memory_write_block(Memory* memory, FILE* data) {
    BlockInfo block_info = {0};
    fgets(block_info.address_and_size,
          sizeof(block_info.address_and_size), data);
    fgetc(data);
    block_info_process(&block_info);
    for (uint16_t i = 0; i < block_info.size_num; ++i) {
        if (feof(data)) {
            error("memory_write_block", "Not enough data bytes!");
        }
        char value_str[TWO_HEX_SYMBOLS + 1] = {0};
        fgets(value_str, sizeof(value_str), data);
        fgetc(data);
        if (strlen(value_str) != TWO_HEX_SYMBOLS) {
            error("memory_write_block", "Wrong length of byte value!");
        }
        for (uint16_t i = 0; i < TWO_HEX_SYMBOLS; ++i) {
            if (!isxdigit(value_str[i])) {
                error("memory_write_block", "Wrong format of byte value!");
            }
        }
        byte value = 0;
        sscanf(value_str, "%"SCNx8, &value);
        memory_write_byte(memory, block_info.address_num + i, value);
    }
}

void block_info_process(BlockInfo* block_info) {
    sscanf(block_info->address_and_size, "%s%s",
           block_info->address_str, block_info->size_str);
    if (strlen(block_info->address_str) != FOUR_HEX_SYMBOLS ||
        strlen(block_info->size_str) != FOUR_HEX_SYMBOLS) {
        error("block_process_info", "Wrong length of address or count value!");
    }
    for (uint16_t i = 0; i < FOUR_HEX_SYMBOLS; ++i) {
        if (!isxdigit(block_info->address_str[i]) ||
            !isxdigit(block_info->size_str[i])) {
            error("block_process_info", "Wrong format of address or count value!");
        }
    }
    sscanf(block_info->address_str, "%"SCNx16, &block_info->address_num);
    sscanf(block_info->size_str, "%"SCNx16, &block_info->size_num);
}

void memory_dump(Memory* memory, address block, uint16_t size) {
    if (word_is_address_odd(block)) {
        error("memory_dump", "Block address is not even!");
    } else if (word_is_address_odd(size)) {
        error("memory_dump", "Block address is not even!");
    }
    uint16_t i = 0;
    for (; i < size && (i + block) < MEMORY_SIZE_IN_BYTES; i += 2) {
        uint16_t value = memory_read_word(memory, block + i);
        printf("%06"PRIo16": %06"PRIo16" %04"PRIx16"\n", block + i, value, value);
    }
    if (i != size) {
        error("memory_dump", "Dump block size is out of memory size!");
    }
}