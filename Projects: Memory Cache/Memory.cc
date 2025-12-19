#include "Memory.h"
#include <iostream>
#include <iomanip>

Memory::Memory(int size) : size(size) {
    bytes = new unsigned char[size];
    for (int i = 0; i < size; ++i) {
        bytes[i] = i % 255;
    }
}

Memory::~Memory() {
    delete[] bytes;
}

unsigned char Memory::getByte(unsigned long address) const {
    return bytes[address];
}

void Memory::setByte(unsigned long address, unsigned char value) {
    bytes[address] = value;
}

int Memory::getSize() const {
    return size;
}

void Memory::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)bytes[i] << " ";
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec;
}
