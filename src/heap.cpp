#include <cstdint>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sys/mman.h>
#include <unistd.h>

#include "heap.h"

Heap::Heap() {
    uint32_t page_size = getpagesize();

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
    this->head->in_use = true;
    return this->head + sizeof(ChunkData);
}

void coalesce_chunk();

void truncate_chunk();

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
