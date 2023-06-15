#include <stdbool.h>
#include "pdp.h"

bool word_is_address_odd(address value) {
    return (bool)(value & (address)0x0001);
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
    byte* first_p = (byte*)&value;
    byte* second_p = first_p + 0x1;
    byte temp = *first_p;
    *first_p = *second_p;
    *second_p = temp;
    return value;
}
