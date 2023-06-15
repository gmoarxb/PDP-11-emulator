#include "pdp.h"

bool word_is_address_odd(address value) {
    return (value & (address)0x0001) == (address)0x0001;
}

word word_make_right_endian(word value) {
    if (word_is_endian_big()) {
        value = word_change_endian(value);
    }
    return value;
}

bool word_is_endian_big() {
    static const word two_bytes = 0x0001;
    const byte first_byte = *((byte*)&two_bytes);
    return (word)first_byte != two_bytes;
}

word word_change_endian(word value) {
    byte* first_byte_ptr = (byte*)&value;
    byte big_byte = *first_byte_ptr;
    *first_byte_ptr = *(first_byte_ptr + 1);
    *(first_byte_ptr + 1) = big_byte;
    return value;
}
