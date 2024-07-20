# Cpp-Heap

A rewrite of my [C memory allocator](https://github.com/Anthony-de-cruz/C-Heap/tree/main) in C++.

C++ classes already use memory allocations, meaning that this malloc implementation uses malloc, which kind of makes this whole thing stupid. Oh well, I just did this to get a bit more comfortable with C++. :)

### Build

Build with:

```sh
cmake -B ./build
cmake --build ./build
```

Run the example with:

```sh
./build/Cpp-Heap
```

### Todo

- [x] Split up chunks
- [x] Truncate chunks
- [ ] Coalesce chunks
- [ ] Free chunks
