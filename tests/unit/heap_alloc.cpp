#include <gtest/gtest.h>
#include <stdexcept>

#include "heap.h"

class HeapAllocTest : public testing::Test {
  protected:
    Heap *heap;

    HeapAllocTest() { heap = new Heap; }
};

TEST_F(HeapAllocTest, Allocation) {
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

TEST_F(HeapAllocTest, OversizedAllocation) {
    try {
        auto alloc = heap->malloc(1000000000);
    } catch (std::runtime_error &exception) {
        return;
    }
    FAIL() << "Should have thrown exception";
}
