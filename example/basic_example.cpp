#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "heap.h"

int main() {

    Heap *heap;

    try {
        heap = new Heap;
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << '\n';
    }

    delete heap;

    return EXIT_SUCCESS;
}
