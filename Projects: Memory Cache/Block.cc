#include "Block.h"
#include <iostream>
#include <iomanip>

Block::Block(int size, Memory* memory)
    : size(size), memory(memory), valid(false), dirty(false) {
    data = new unsigned char[size];
}

Block::~Block() {
    delete[] data;
}

unsigned char Block::read(int offset) {
    updateTimestamp();
    return data[offset];
}

void Block::write(int offset, unsigned char value) {
    updateTimestamp();
    data[offset] = value;
    dirty = true;
}

void Block::loadFromMemory(unsigned long address) {
    unsigned long baseAddress = address - (address % size);
    for (int i = 0; i < size; ++i) {
        data[i] = memory->getByte(baseAddress + i);
    }
    valid = true;
    dirty = false;
}

void Block::saveToMemory() {
    unsigned long baseAddress = tag * size;
    for (int i = 0; i < size; ++i) {
        memory->setByte(baseAddress + i, data[i]);
    }
    dirty = false;
}

unsigned long Block::getTag() const {
    return tag;
}

void Block::setTag(unsigned long tag) {
    this->tag = tag;
}

bool Block::isValid() const {
    return valid;
}

void Block::setValid(bool valid) {
    this->valid = valid;
}

bool Block::isDirty() const {
    return dirty;
}

void Block::setDirty(bool dirty) {
    this->dirty = dirty;
}

long Block::getTimestamp() const {
    return timestamp;
}

void Block::updateTimestamp() {
    timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(clock.now().time_since_epoch()).count();
}

void Block::display() const {
    std::cout << "    valid: " << valid << "    tag: " << tag << "    dirty: " << dirty << "    timestamp: " << timestamp << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[i] << " ";
    }
    std::cout << std::dec << std::endl;
}
