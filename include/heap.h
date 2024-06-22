#ifndef HEAP_H
#define HEAP_H

#include <cstdint>

class Heap {

  private:
    typedef struct ChunkData {
        std::uint32_t size;
        bool in_use;
        void *next;
        void *prev;
    } ChunkData;

    ChunkData *head;
    std::uint32_t available_space;

  public:
    Heap();
    void *alloc(std::uint32_t size);
    void *realloc(void *chunk, std::uint32_t new_size);
    void free(void *chunk);
    void free_heap();
    ~Heap();
};

#endif // !HEAP_H
