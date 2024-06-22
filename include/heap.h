#ifndef HEAP_H
#define HEAP_H

#include "chunk.h"
#include <memory>

class Heap {

  private:
    std::shared_ptr<Chunk> head;

  public:
    Heap();
    void free_heap();
    ~Heap();
};

#endif // !HEAP_H
