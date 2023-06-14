#ifndef PDP_11_EMULATOR_H_
#define PDP_11_EMULATOR_H_

#include <stdint.h>
#include <inttypes.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint16_t address;

#define MEMORY_SIZE (64 * 1024)

void byte_write(address destination, byte value);
byte byte_read(address source);
void word_write(address destination, word value);
word word_read(address source);

#endif  // PDP_11_EMULATOR_H_