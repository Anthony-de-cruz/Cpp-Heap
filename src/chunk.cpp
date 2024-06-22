#include "chunk.h"

Chunk::Chunk(void *memory_ptr, unsigned int size) {

    this->memory_ptr = memory_ptr;
    this->size = size;
    this->in_use = false;
    this->next = this;
    this->prev = this;
}
