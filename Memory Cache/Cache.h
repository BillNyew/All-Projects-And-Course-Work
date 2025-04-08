#ifndef CACHE_H
#define CACHE_H

#include "Memory.h"
#include "Set.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

class Cache {
private:
    int cacheSize;
    int blockSize;
    int setAssociativity;
    int numSets;
    Set** sets;
    Memory* memory;
    AddressDecoder* decoder;
    PerformanceCounter* performanceCounter;

public:
    Cache(Memory* memory, int cacheSize, int blockSize, int setAssociativity);
    ~Cache();

    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);
    void display() const;
};

#endif

