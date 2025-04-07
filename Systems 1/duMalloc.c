#include "duMalloc.h"
#include <stdio.h>

#define HEAP_SIZE (128*8)

// Structure for the header of each memory block
typedef struct memoryBlockHeader {
    int size; // size of the reserved block
    struct memoryBlockHeader* next;  // the next block in the integrated free list
} memoryBlockHeader;

unsigned char heap[HEAP_SIZE]; // The heap
memoryBlockHeader* freeListHead; // The head of the free list

void duInitMalloc() {
    // Initialize all memory in the heap to 0
    for (int i = 0; i < HEAP_SIZE; ++i) {
        heap[i] = 0;
    }

    // Create a single large free block at the start of the heap
    memoryBlockHeader* initialBlock = (memoryBlockHeader*)heap;
    initialBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
    initialBlock->next = NULL;
    freeListHead = initialBlock;
}

void* duMalloc(int size) {
    // Implement duMalloc according to the specifications
    // This function should return a pointer to the allocated memory
    size = (size % 8 == 0) ? size : size + (8 - (size % 8)); // Round up to the next multiple of 8
    memoryBlockHeader* currentBlock = freeListHead;
    memoryBlockHeader* prevBlock = NULL;

    while (currentBlock != NULL) {
        if (currentBlock->size >= size) {
            // Split the block
            int remainingSize = currentBlock->size - size;
            currentBlock->size = size;

            // Create a new free block after the allocated block
            memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)((unsigned char*)currentBlock + sizeof(memoryBlockHeader) + size);
            newFreeBlock->size = remainingSize - sizeof(memoryBlockHeader);
            newFreeBlock->next = currentBlock->next;

            // Update the free list
            if (prevBlock != NULL) {
                prevBlock->next = newFreeBlock;
            } else {
                freeListHead = newFreeBlock;
            }

            return (void*)((unsigned char*)currentBlock + sizeof(memoryBlockHeader));
        }

        prevBlock = currentBlock;
        currentBlock = currentBlock->next;
    }

    return NULL; // No suitable block found
}

void duFree(void* ptr) {
    // Implement duFree according to the specifications
    memoryBlockHeader* blockHeader = (memoryBlockHeader*)((unsigned char*)ptr - sizeof(memoryBlockHeader));

    // Find the correct location to insert the block back into the free list
    memoryBlockHeader* currentBlock = freeListHead;
    memoryBlockHeader* prevBlock = NULL;

    while (currentBlock != NULL && currentBlock < blockHeader) {
        prevBlock = currentBlock;
        currentBlock = currentBlock->next;
    }

    // Insert the block back into the free list
    if (prevBlock != NULL) {
        prevBlock->next = blockHeader;
    } else {
        freeListHead = blockHeader;
    }

    blockHeader->next = currentBlock;

    // Coalesce adjacent free blocks
    if (currentBlock != NULL && (unsigned char*)blockHeader + sizeof(memoryBlockHeader) + blockHeader->size == (unsigned char*)currentBlock) {
        blockHeader->size += currentBlock->size + sizeof(memoryBlockHeader);
        blockHeader->next = currentBlock->next;
    }
}

void duMemoryDump() {
    // Implement duMemoryDump to print the memory address and size of all blocks on the free list
    memoryBlockHeader* currentBlock = freeListHead;
    printf("MEMORY DUMP\nFree List\n");
    while (currentBlock != NULL) {
        printf("Block at %p, size %d\n", (void*)currentBlock, currentBlock->size);
        currentBlock = currentBlock->next;
    }
}