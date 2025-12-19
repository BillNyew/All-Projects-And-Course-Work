#ifndef BLOCK_H
#define BLOCK_H

#include "Memory.h"
#include <chrono>

class Block {
private:
    unsigned char* data;
    int size;
    Memory* memory;
    unsigned long tag;
    bool valid;
    bool dirty;
    long timestamp;
    std::chrono::high_resolution_clock clock;

public:
    Block(int size, Memory* memory);
    ~Block();

    unsigned char read(int offset);
    void write(int offset, unsigned char value);

    void loadFromMemory(unsigned long address);
    void saveToMemory();

    unsigned long getTag() const;
    void setTag(unsigned long tag);
    bool isValid() const;
    void setValid(bool valid);
    bool isDirty() const;
    void setDirty(bool dirty);
    long getTimestamp() const;
    void updateTimestamp();

    void display() const;
};

#endif
