#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#include "../pdp.h"

#define LINE_MAX_SIZE (0x1 << 0x4)  // 16

typedef struct block {
    char address_and_size[LINE_MAX_SIZE];
    char address_str[LINE_MAX_SIZE];
    char size_str[LINE_MAX_SIZE];
    address address_num;
    uint16_t size_num;
} Block;

void memory_write_block(Memory* memory, FILE* data);
void block_process_info(Block* block);

void memory_load_data(Memory* memory, const char* file_name) {
    FILE* data = fopen(file_name, "r");
    if (!data || ferror(data)) {
        error("memory_load_data", "Unable to open file!");
    }
    while (!feof(data)) {
        memory_write_block(memory, data);
        if (ferror(data)) {
            error("memory_load_data", "ferror(data) is true!");
        }
    }
}

void memory_write_block(Memory* memory, FILE* data) {
    Block block = {0};
    fgets(block.address_and_size, LINE_MAX_SIZE, data);
    if (ferror(data)) {
        error("memory_write_block", "ferror(data) is true!");
    }
    block_process_info(&block);
    for (uint16_t i = 0; i < block.size_num; ++i) {
        char value_str[LINE_MAX_SIZE] = {0};
        fgets(value_str, LINE_MAX_SIZE, data);
        byte value = 0;
        sscanf(value_str, "%"SCNx8, &value);
        memory->bytes[block.address_num + (address)i] = value;
    }
}

void block_process_info(Block* block) {
    sscanf(block->address_and_size, "%s%s", block->address_str, block->size_str);
    if (strlen(block->address_str) != 4 || strlen(block->size_str) != 4) {
        error("block_process_info", "Wrong length of address or count!");
    }
    for (uint16_t i = 0; i < 4; ++i) {
        if (!isxdigit(block->address_str[i]) || !isxdigit(block->size_str[i])) {
            error("block_process_info", "Wrong format of address or count!");
        }
    }
    sscanf(block->address_str, "%"SCNx16, &block->address_num);
    sscanf(block->size_str, "%"SCNx16, &block->size_num);
}

void memory_dump(Memory* memory, address block, uint16_t size) {
    for (uint16_t i = 0; i + block < MEMORY_SIZE_IN_BYTES; i += 2) {
        if (i == size * 2) {
            break;
        } else {
            word value = word_make_right_endian(memory->words[(block + (address)i) >> 0x1]);
            printf("%06"PRIo16": %06"PRIo16" %04"PRIx16"\n", block + (address)i, value, value);
        }
    }
}