#ifndef PDP_11_EMULATOR_H_
#define PDP_11_EMULATOR_H_

#include <stdint.h>
#include <inttypes.h>

typedef uint8_t byte;  // byte is 8 bits
typedef uint16_t word;  // word is 2 bytes
typedef uint16_t address;  // represets 2^16 values

#define WORD_SIZE_IN_BYTES 2  // word is 2 bytes
#define MEMORY_SIZE_IN_BYTES (64 * 1024)  // 64 kbytes

typedef struct memory {
    union {
        byte bytes[MEMORY_SIZE_IN_BYTES];
        word words[MEMORY_SIZE_IN_BYTES / WORD_SIZE_IN_BYTES];
    };
} Memory;

void memory_write_byte(Memory* memory, address destination, byte value);
byte memory_read_byte(Memory* memory, address source);
void memory_write_word(Memory* memory, address destination, word value);
word memory_read_word(Memory* memory, address source);

#endif  // PDP_11_EMULATOR_H_