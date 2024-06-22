#include "chunk.h"

Chunk::Chunk(unsigned int size) {

    this->size = size;
    this->in_use = false;
    this->next = this;
    this->prev = this;
}
