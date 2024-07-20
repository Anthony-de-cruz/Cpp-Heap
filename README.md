# Cpp-Heap

A rewrite of my [C memory allocator](https://github.com/Anthony-de-cruz/C-Heap/tree/main) in C++.

C++ classes already use memory allocations, meaning that this malloc implementation uses malloc, which kind of makes this whole thing stupid. Oh well, I just did this to get a bit more comfortable with C++. :)

### Build

Build with:

```sh
cmake -B build
cmake --build build -j 12
```

Run tests with:

```sh
GTEST_COLOR=1 ctest --test-dir build --output-on-failure -j 12
```

Run the example with:

```sh
./build/Cpp-Heap
```

### Todo

- [x] Split up chunks
- [x] Truncate chunks
- [x] Coalesce chunks
- [x] Free chunks
- [ ] Write tests
