#include <cmath>
#include <cstdint>
#include <cstdio>
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
}

void *Heap::alloc(uint32_t size) {
    std::cout << "alloc @ " << this->head << '\n';

    this->head->in_use = true;
    this->head->size = this->head->size - sizeof(ChunkData);
    return this->head + sizeof(ChunkData);
}

void Heap::free(void *chunk_ptr) {
    ChunkData *chunk_data = (ChunkData *)chunk_ptr - sizeof(ChunkData);

    std::cout << "free @ " << chunk_data << '\n';

    chunk_data->in_use = false;
}

void coalesce_chunk();

void truncate_chunk();

void Heap::print_chunk(std::ostream &stream, void *chunk_ptr) {
    ChunkData *chunk_data = (ChunkData *)chunk_ptr - sizeof(ChunkData);

    stream << "chunk @ " << chunk_data << '\n'
           << "    size: " << chunk_data->size << '\n'
           << "    in use: " << chunk_data->in_use << '\n'
           << "    next chunk @ " << chunk_data->next << '\n'
           << "    prev chunk @ " << chunk_data->prev << '\n';

    unsigned int row_len = sizeof(ChunkData);

    // Print hex table
    for (int col = 0; col < (row_len * 3) + 6; col++) {
        stream << '-';
    }
    stream << '\n';
    for (std::uint32_t row = 0; row < std::ceil(chunk_data->size / row_len);
         row++) {
        stream << std::setw(4) << std::setfill('0') << std::dec << row * row_len
               << "|  ";

        for (std::uint32_t col = 0; col < row_len; col++) {
            // Pull out uint8 data at each address, cast to int and print as hex
            std::uint8_t *ptr = (std::uint8_t *)((std::uintptr_t)chunk_data +
                                                 (row * row_len) + col);
            int byte = *ptr;
            stream << std::setw(2) << std::setfill('0') << std::hex
                   << std::uppercase << std::noskipws << byte << " ";
        }
        stream << '\n';
    }
    for (int col = 0; col < (row_len * 3) + 6; col++) {
        stream << '-';
    }
    stream << '\n';
}

void Heap::print_heap(std::ostream &stream) {

    std::cout << "heap " << '\n'
              << "    chunk metadata size: " << sizeof(ChunkData) << '\n'
              << "    chunk count: " << "--" << '\n';

    // Should traverse through and print all the chunks
    this->print_chunk(stream, this->head + sizeof(ChunkData));
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
