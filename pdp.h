#ifndef PDP_11_EMULATOR_H_
#define PDP_11_EMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t byte;  // byte is 8 bits
typedef uint16_t word;  // word is 2 bytes
typedef uint16_t address;  // represets 2^16 values

#define MEMORY_SIZE_IN_BYTES (0x1 << 0x6 * 0x1 << 0xA)  // 64 kbytes

typedef struct memory {
    union {
        byte bytes[MEMORY_SIZE_IN_BYTES];
        word words[MEMORY_SIZE_IN_BYTES >> 0x1];
    };
} Memory;

void memory_write_byte(Memory* memory, address destination, byte value);
byte memory_read_byte(Memory* memory, address source);
void memory_write_word(Memory* memory, address destination, word value);
word memory_read_word(Memory* memory, address source);

void error(char* function_name, char* message);

#endif  // PDP_11_EMULATOR_H_