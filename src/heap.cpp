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

    // this->head = new Chunk(map, page_size);
    this->head = std::shared_ptr<Chunk>(new Chunk(map, page_size));
}

void Heap::free_heap() {
    // System call to free the mapped memory
    int status = munmap((void *)this->head->get_memory_ptr(), getpagesize());
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
