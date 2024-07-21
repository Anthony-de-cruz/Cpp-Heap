#ifndef HEAP_H
#define HEAP_H

#include <cstdint>
#include <ostream>

class Heap {

  private:
    struct ChunkData;

    ChunkData *head;

    /**
     * Truncate the chunk to the new size,
     * creating a new chunk with the leftovers.
     */
    static void truncate_chunk(Heap::ChunkData *free_chunk,
                               std::uint32_t new_size);

    /**
     * Coalesce chunk with it's free neighbours if there are any.
     */
    void coalesce_chunk(Heap::ChunkData *chunk);

    /**
     * Print memory and metadata of chunk to stream.
     */
    static void print_chunk(std::ostream &stream, void *chunk,
                            unsigned int index);

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
     * Print heap metadata and all chunks.
     */
    void print_heap(std::ostream &stream);

    /**
     *
     */
    ~Heap();
};

#endif // !HEAP_H
