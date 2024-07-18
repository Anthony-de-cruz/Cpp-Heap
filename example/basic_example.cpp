#include <cstdlib>
#include <cstring>
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

    char *string1 = (char *)heap->malloc(32);
    std::strcat(string1, "Hi\n");

    std::cout << string1;

    heap->print_heap(std::cout);

    heap->free(string1);

    delete heap;

    return EXIT_SUCCESS;
}
