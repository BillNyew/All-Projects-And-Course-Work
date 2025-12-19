#include "Cache.h"
#include <cmath>
#include <iostream>

Cache::Cache(Memory* memory, int cacheSize, int blockSize, int setAssociativity)
    : memory(memory), cacheSize(cacheSize), blockSize(blockSize), setAssociativity(setAssociativity) {
    numSets = cacheSize / (blockSize * setAssociativity);
    sets = new Set*[numSets];
    for (int i = 0; i < numSets; ++i) {
        sets[i] = new Set(memory, setAssociativity, blockSize);
    }
    decoder = new AddressDecoder(log2(numSets), log2(blockSize));
    performanceCounter = new PerformanceCounter();
}

Cache::~Cache() {
    for (int i = 0; i < numSets; ++i) {
        delete sets[i];
    }
    delete[] sets;
    delete decoder;
    delete performanceCounter;
}

unsigned char Cache::read(unsigned long address) {
    int setIndex = decoder->getSetIndex(address);
    unsigned char data = sets[setIndex]->read(address);
    if (data != 0) {
        performanceCounter->incrementHits();
    } else {
        performanceCounter->incrementMisses();
    }
    return data;
}

void Cache::write(unsigned long address, unsigned char value) {
    int setIndex = decoder->getSetIndex(address);
    sets[setIndex]->write(address, value);
    performanceCounter->incrementWritebacks();
}

void Cache::display() const {
    for (int i = 0; i < numSets; ++i) {
        std::cout << "Set " << i << std::endl;
        sets[i]->display();
    }
    performanceCounter->display();
}

