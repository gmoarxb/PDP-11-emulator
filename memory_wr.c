#include "pdp.h"

void memory_write_byte(Memory* memory, address destination, byte value) {
    if (!memory) {
        error("memory_write_byte", "Memory not initialized!");
    }
    memory->bytes[destination] = value;
}

byte memory_read_byte(Memory* memory, address source) {
    if (!memory) {
        error("memory_read_byte", "Memory not initialized!");
    }
    return memory->bytes[source];
}

void memory_write_word(Memory* memory, address destination, word value) {
    if (!memory) {
        error("memory_write_word", "Memory not initialized!");
    } else if (word_is_address_odd(destination)) {
        error("memory_write_word", "Not even address for word!");
    }
    memory->words[destination >> 0x1] = word_make_right_endian(value);
}

word memory_read_word(Memory* memory, address source) {
    if (!memory) {
        error("memory_read_word", "Memory not initialized!");
    } else if (word_is_address_odd(source)) {
        error("memory_write_word", "Not even address for word!");
    }
    return word_make_right_endian(memory->words[source >> 0x1]);
}