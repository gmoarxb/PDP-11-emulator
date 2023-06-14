#include "pdp.h"

void memory_write_byte(Memory* memory, address destination, byte value) {
    if (memory == NULL) {
        error("memory_write_byte", "Memory not initialized!");
    }
    memory->bytes[destination] = value;
}

byte memory_read_byte(Memory* memory, address source) {
    if (memory == NULL) {
        error("memory_read_byte", "Memory not initialized!");
    }
    return memory->bytes[source];
}

void memory_write_word(Memory* memory, address destination, word value) {

}
word memory_read_word(Memory* memory, address source) {
    
}