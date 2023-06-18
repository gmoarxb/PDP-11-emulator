#ifndef PDP_11_EMULATOR_H_
#define PDP_11_EMULATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

typedef uint8_t byte;  // byte is 8 bits
typedef uint16_t word;  // word is 2 bytes
typedef uint16_t address;  // represents 2^16 values

#define MEMORY_SIZE_IN_BYTES (1 << 16)  // 64 kbytes = 64 * 1024 = 2^6 * 2^10

typedef union memory {
        byte bytes[MEMORY_SIZE_IN_BYTES];
        word words[MEMORY_SIZE_IN_BYTES >> 1];
} Memory;

typedef word registers[8];

typedef struct pdp_11 {
    Memory memory;
    union {
        registers R;
        struct {
            word fill[7];
            word PC;
        };
    };
} Pdp11;

void error(char* function_name, char* message);

bool word_is_address_odd(address value);
word word_make_right_endian(word value);
bool word_is_endian_big();
word word_change_endian(word value);

void memory_write_byte(Memory* memory, address destination, byte value);
byte memory_read_byte(Memory* memory, address source);
void memory_write_word(Memory* memory, address destination, word value);
word memory_read_word(Memory* memory, address source);

void memory_load_data(Memory* memory, const char* file_name);
void memory_write_block(Memory* memory, address block, uint16_t size, FILE* data);
void memory_dump(Memory* memory, address block, uint16_t size);

typedef enum log_level {
    LOG_WARNING, LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_ERROR
} LogLevel;

extern LogLevel current_log_level;

void log_state(LogLevel log_level, const char* const message, ...);
void log_level_print(LogLevel log_level);

#endif  // PDP_11_EMULATOR_H_