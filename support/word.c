#include <stdbool.h>
#include "../pdp.h"

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
    static bool result = false;
    static bool checked = false;
    if (!checked) {
        const word two_bytes = 0x0001;
        const byte first_byte = *((byte*)&two_bytes);
        result = (bool)((word)first_byte != two_bytes);
        checked = true;
    }
    return result;
}

word word_change_endian(word value) {
    return (value >> 8) | (value << 8);
}
