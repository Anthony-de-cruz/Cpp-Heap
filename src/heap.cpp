#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <sys/mman.h>
#include <unistd.h>

#include "heap.h"

Heap::Heap() {
    std::uint32_t page_size = getpagesize();

    // System call to get a page-aligned memory map
    void *map = mmap(nullptr, page_size, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (map == (void *)-1) {
        throw std::runtime_error("Memory map retrival failed");
    }

    ChunkData *head = (ChunkData *)map;
    head->size = page_size;
    head->in_use = false;
    head->next = head;
    head->prev = head;

    this->head = head;

    this->truncate_chunk(head, 100);
}

void *Heap::malloc(std::uint32_t size) {
    void *alloc_ptr = (void *)((std::uintptr_t)this->head + sizeof(ChunkData));
    std::cout << "alloc @ " << alloc_ptr << '\n';
    std::cout << "    " << this->head << ", " << sizeof(ChunkData) << '\n';

    this->head->in_use = true;
    this->head->size = this->head->size - sizeof(ChunkData);
    return alloc_ptr;
}

void *Heap::calloc(std::uint32_t size) { return nullptr; }

void Heap::free(void *chunk_ptr) {

    std::cout << "free @ " << chunk_ptr << '\n';

    ChunkData *chunk_data =
        (ChunkData *)((std::uintptr_t)chunk_ptr - sizeof(ChunkData));
    chunk_data->in_use = false;
}

void Heap::truncate_chunk(Heap::ChunkData *chunk, std::uint32_t new_size) {

    std::uint32_t metadata_size = sizeof(ChunkData);

    // The new size must be smaller
    assert(new_size < chunk->size + metadata_size);

    // The chunk must be truncated down to a
    // multiple of the size of the metadata
    std::uint32_t truncated_size =
        new_size + (metadata_size - (new_size % metadata_size));
    std::uint32_t leftover_space = chunk->size - truncated_size;

    chunk->size = truncated_size;

    // Create a new chunk from the leftovers
    ChunkData *new_chunk =
        (ChunkData *)((char *)chunk + chunk->size + metadata_size);
    *new_chunk = {.size = leftover_space - metadata_size,
                  .in_use = 0,
                  .next = chunk->next,
                  .prev = chunk};

    // Update the new chunk's neighbours
    chunk->next->prev = new_chunk;
    chunk->next = new_chunk;
}

void Heap::coalesce_chunk(Heap::ChunkData *chunk) { assert(false); }

void print_hex_table(std::ostream &stream, void *memory_ptr,
                     std::uint32_t bytes, unsigned int columns) {
    const int rows = (bytes + (columns - 1)) / columns;
    int byte_index = 0;

    for (int col = 0; col < (columns * 3) + 16; col++) {
        stream << '-';
    }
    stream << '\n';

    for (std::uint32_t row = 0; row < rows; row++) {
        // Print the pointer for this row
        stream << (void *)((ulong)memory_ptr + (byte_index)) << "|  ";

        for (std::uint32_t col = 0; col < columns && byte_index < bytes;
             col++, byte_index++) {
            // Pull out uint8 data at each address, cast to int and print as hex
            std::uint8_t *byte_ptr = (std::uint8_t *)memory_ptr;
            int byte = byte_ptr[byte_index];

            if (byte != 0) {
                stream << std::setw(2) << std::noskipws << std::setfill('0')
                       << std::hex << std::uppercase << byte << ' ';
            } else {
                stream << ".." << ' ';
            }
        }
        stream << '\n';
    }
    for (int col = 0; col < (columns * 3) + 16; col++) {
        stream << '-';
    }
    stream << '\n';
}

void Heap::print_chunk(std::ostream &stream, void *chunk_ptr,
                       unsigned int index) {
    ChunkData *chunk_data =
        (ChunkData *)((std::uintptr_t)chunk_ptr - sizeof(ChunkData));

    stream << "chunk " << index << '\n'
           << "    metadata @ " << chunk_data << '\n'
           << "        size: " << std::dec << chunk_data->size << '\n'
           << "        in use: " << chunk_data->in_use << '\n'
           << "        next chunk @ " << chunk_data->next << '\n'
           << "        prev chunk @ " << chunk_data->prev << '\n'
           << "    memory @ " << chunk_ptr << '\n';
    print_hex_table(stream, chunk_data, chunk_data->size, sizeof(ChunkData));
}

void Heap::print_heap(std::ostream &stream) {

    std::cout << "heap " << '\n'
              << "    chunk metadata size: " << sizeof(ChunkData) << '\n';

    // Should traverse through and print all the chunks
    Heap::ChunkData *chunk = this->head;
    unsigned int index = 0;
    do {
        this->print_chunk(
            stream, (void *)((std::uintptr_t)chunk + sizeof(ChunkData)), index);
        chunk = chunk->next;
        index++;
    } while (chunk != head);
}

void Heap::free_heap() {
    // System call to free the mapped memory
    int status = munmap((void *)this->head, getpagesize());
    if (status) {
        throw std::runtime_error("Memory map free failed");
    }

    // Should also traverse and free up the chunks, given that they are arranged
    // as a data structure, they might have circular references that smart
    // pointers don't free up
}

Heap::~Heap() {
    try {
        this->free_heap();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what();
    }
}
