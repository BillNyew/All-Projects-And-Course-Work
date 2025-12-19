#include "Set.h"
#include <iostream>
#include <cmath>  // Include the cmath library for std::log2

Set::Set(Memory* memory, int numBlocks, int blockSize)
    : memory(memory), numBlocks(numBlocks) {
    blocks = new Block*[numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        blocks[i] = new Block(blockSize, memory);
    }
    decoder = new AddressDecoder(std::log2(numBlocks), std::log2(blockSize));
}

Set::~Set() {
    for (int i = 0; i < numBlocks; ++i) {
        delete blocks[i];
    }
    delete[] blocks;
    delete decoder;
}

unsigned char Set::read(unsigned long address) {
    int blockOffset = decoder->getBlockOffset(address);
    unsigned long tag = decoder->getTag(address);

    for (int i = 0; i < numBlocks; ++i) {
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag) {
            updateLRU(blocks[i]);
            return blocks[i]->read(blockOffset);
        }
    }

    Block* block = getFreeBlock();
    if (!block) {
        block = getLRUBlock();
        if (block->isDirty()) {
            block->saveToMemory();
        }
    }
    block->loadFromMemory(address);
    block->setTag(tag);
    block->setValid(true);
    updateLRU(block);
    return block->read(blockOffset);
}

void Set::write(unsigned long address, unsigned char value) {
    int blockOffset = decoder->getBlockOffset(address);
    unsigned long tag = decoder->getTag(address);

    for (int i = 0; i < numBlocks; ++i) {
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag) {
            updateLRU(blocks[i]);
            blocks[i]->write(blockOffset, value);
            blocks[i]->setDirty(true);
            return;
        }
    }

    Block* block = getFreeBlock();
    if (!block) {
        block = getLRUBlock();
        if (block->isDirty()) {
            block->saveToMemory();
        }
    }
    block->loadFromMemory(address);
    block->setTag(tag);
    block->setValid(true);
    updateLRU(block);
    block->write(blockOffset, value);
    block->setDirty(true);
}

void Set::display() const {
    for (int i = 0; i < numBlocks; ++i) {
        std::cout << "  Block " << i << ":" << std::endl;
        blocks[i]->display();
    }
}

Block* Set::getLRUBlock() {
    Block* lruBlock = blocks[0];
    for (int i = 1; i < numBlocks; ++i) {
        if (blocks[i]->getTimestamp() < lruBlock->getTimestamp()) {
            lruBlock = blocks[i];
        }
    }
    return lruBlock;
}

Block* Set::getFreeBlock() {
    for (int i = 0; i < numBlocks; ++i) {
        if (!blocks[i]->isValid()) {
            return blocks[i];
        }
    }
    return nullptr;
}

void Set::updateLRU(Block* block) {
    block->updateTimestamp();
}
