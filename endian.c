#include "pdp.h"

bool is_big_endian() {
    static const word two_bytes = 0x0001;
    const byte first_byte = *((byte*)&two_bytes);
    return (word)first_byte != two_bytes;
}

word change_endian(word value) {
    byte* first_byte_ptr = (byte*)&value;
    byte big_byte = *first_byte_ptr;
    *first_byte_ptr = *(first_byte_ptr + 1);
    *(first_byte_ptr + 1) = big_byte;
    return value;
}

word get_right_endian_word(word value) {
    if (is_big_endian()) {
        value = change_endian(value);
    }
    return value;
}
