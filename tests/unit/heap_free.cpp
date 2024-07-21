#include <gtest/gtest.h>
#include <stdexcept>

#include "heap.h"

class HeapFreeTest : public testing::Test {
  protected:
    Heap *heap;
    void *ptr_1;
    void *ptr_2;
    void *ptr_3;

    HeapFreeTest() {
        heap = new Heap;
        ptr_1 = heap->malloc(1);
        ptr_2 = heap->malloc(1);
        ptr_3 = heap->malloc(1);
    }
};

TEST_F(HeapFreeTest, Free) {
    try {
        heap->free(ptr_1);
    } catch (std::runtime_error &exception) {
        FAIL() << exception.what();
    }
}
