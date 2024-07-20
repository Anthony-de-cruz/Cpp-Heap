#include <gtest/gtest.h>
#include <stdexcept>

#include "heap.h"

TEST(HeapTest, Initialisation) {
    try {
        auto heap = new Heap;
    } catch (std::runtime_error &exception) {
        FAIL() << exception.what();
    }
}

TEST(HeapTest, Allocation) {
    auto heap = new Heap;

    char *string1;
    try {
        string1 = (char *)heap->malloc(1);
    } catch (std::runtime_error &exception) {
        FAIL() << exception.what();
    }

    strcat(string1, "a\n");

    heap->free(string1);
    heap->print_heap(std::cout);
}

TEST(HeapTest, OversizedAllocation) {

    auto heap = new Heap;
    try {
        auto alloc = heap->malloc(1000000000);
    } catch (std::runtime_error &exception) {
        return;
    }
    FAIL() << "Should have thrown exception";
}
