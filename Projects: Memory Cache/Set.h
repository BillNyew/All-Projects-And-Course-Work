#ifndef SET_H
#define SET_H

#include "Block.h"
#include "Memory.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

class Set {
private:
    int numBlocks;
    Block** blocks;
    Memory* memory;
    AddressDecoder* decoder;
    PerformanceCounter* performanceCounter;

    Block* getLRUBlock();
    Block* getFreeBlock();
    void updateLRU(Block* block);

public:
    Set(Memory* memory, int numBlocks, int blockSize);
    ~Set();

    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);
    void display() const;
};

#endif
