#include "pdp.h"

bool is_big_endian() {
    static const uint16_t two_bytes = 0x1;
    const uint8_t first_byte = *((uint8_t*)&two_bytes);
    return first_byte != two_bytes;
}