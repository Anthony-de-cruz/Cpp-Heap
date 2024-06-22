#ifndef CHUNK_H
#define CHUNK_H

class Chunk {

  private:
    unsigned int size;
    bool in_use;
    Chunk *next;
    Chunk *prev;

  public:
    Chunk(unsigned int size);
};

#endif // !CHUNK_H
