#ifndef CHUNK_H
#define CHUNK_H

class Chunk {

  private:
    void *memory_ptr;
    unsigned int size;
    bool in_use;
    Chunk *next;
    Chunk *prev;

  public:
    Chunk(void *memory_ptr, unsigned int size);

    inline void *get_memory_ptr() { return this->memory_ptr; }
};

#endif // !CHUNK_H
