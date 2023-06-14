#include "pdp.h"

bool is_big_endian() {
    static const word two_bytes = 0x0001;
    const byte first_byte = *((byte*)&two_bytes);
    return (word)first_byte != two_bytes;
}

bool is_little_endian() {
    return !is_big_endian();
}

word swap_endian(word value) {
    byte* first_byte_ptr = (byte*)&value;
    byte big_byte = *first_byte_ptr;
    *first_byte_ptr = *(first_byte_ptr + 1);
    *(first_byte_ptr + 1) = big_byte;
    return value;
}