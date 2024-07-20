#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "heap.h"

int main() {

    Heap *heap;

    try {
        heap = new Heap;
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << '\n';
    }

    char *string1;
    char *string2;
    char *string3;
    try {
        string1 = (char *)heap->malloc(3);
        string2 = (char *)heap->malloc(3);
        string3 = (char *)heap->malloc(3);
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << '\n';
    }
    std::strcat(string1, "a\n");
    std::strcat(string2, "b\n");
    std::strcat(string3, "c\n");

    heap->free(string1);
    heap->free(string2);
    heap->free(string3);
    heap->print_heap(std::cout);

    delete heap;

    return EXIT_SUCCESS;
}
