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
    /**
     * Mid-memory-allocation.
     */
    void *malloc(std::uint32_t size);

    /**
     * Clear-memory-allocation.
     */
    void *calloc(std::uint32_t size);

    /**
     * Recreate chunk to new size.
     */
    void *realloc(void *chunk, std::uint32_t new_size);

    /**
     * Mark chunk for cleanup.
     */
    void free(void *chunk);

    /**
     * Print memory and metadata of chunk to stream.
     */
    void print_chunk(std::ostream &stream, void *chunk);

    /**
     * Print heap metadata and all chunks.
     */
    void print_heap(std::ostream &stream);

    /**
     *
     */
    ~Heap();
};

#endif // !HEAP_H
