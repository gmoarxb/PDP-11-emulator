#ifndef PDP_11_EMULATOR_H_
#define PDP_11_EMULATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t byte;  // byte is 8 bits
typedef uint16_t word;  // word is 2 bytes
typedef uint16_t address;  // represents 2^16 values

#define MEMORY_SIZE_IN_BYTES (0x1 << 0x6 * 0x1 << 0xA)  // 2^64 * 2^10 = 64 kbytes

typedef struct memory {
    union {
        byte bytes[MEMORY_SIZE_IN_BYTES];
        word words[MEMORY_SIZE_IN_BYTES >> 0x1];
    };
} Memory;

bool word_is_address_odd(address value);
word word_make_right_endian(word value);
bool word_is_endian_big();
word word_change_endian(word value);

void memory_write_byte(Memory* memory, address destination, byte value);
byte memory_read_byte(Memory* memory, address source);
void memory_write_word(Memory* memory, address destination, word value);
word memory_read_word(Memory* memory, address source);

void memory_load_data();

void error(char* function_name, char* message);

void memory_load_data(Memory* memory, const char* file_name);
void memory_dump(Memory* memory, address block, uint16_t size);

#endif  // PDP_11_EMULATOR_H_