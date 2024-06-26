#ifndef HEAP_H
#define HEAP_H

#include <cstdint>
#include <ostream>

class Heap {

  private:
    typedef struct ChunkData {
        std::uint32_t size;
        bool in_use;
        ChunkData *next;
        ChunkData *prev;
    } ChunkData;

    ChunkData *head;
    std::uint32_t available_space;

    void free_heap();

  public:
    Heap();
    void *alloc(std::uint32_t size);
    void *realloc(void *chunk, std::uint32_t new_size);
    void free(void *chunk);
    void print_chunk(std::ostream &stream, void *chunk);
    void print_heap(std::ostream &stream);
    ~Heap();
};

#endif // !HEAP_H
