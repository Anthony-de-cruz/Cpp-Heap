#include <gtest/gtest.h>
#include <stdexcept>

#include "heap.h"

class HeapInitTest : public testing::Test {};

TEST(HeapInitTest, Initialisation) {
    try {
        auto heap = new Heap;
    } catch (std::runtime_error &exception) {
        FAIL() << exception.what();
    }
}
