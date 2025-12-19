#include "duMalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_SIZE (1024)
#define MANAGED_LIST_SIZE (HEAP_SIZE / 8)

typedef struct memoryBlockHeader {
    int free; // 0 - used, 1 - free
    int size; // size of the reserved block
    int managedIndex; // the unchanging index in the managed array
    struct memoryBlockHeader* next;
} memoryBlockHeader;

unsigned char heap[3][HEAP_SIZE]; // Two young generations and one old generation
memoryBlockHeader* freeListHead[3];
void* managedList[MANAGED_LIST_SIZE];
int managedListSize = 0;
int allocationMethod = FIRST_FIT;
int currentHeap = 0;

void duInitManagedList() {
    for (int i = 0; i < MANAGED_LIST_SIZE; ++i) {
        managedList[i] = NULL;
    }
    managedListSize = 0;
}

void duInitMalloc(int fitType) {
    allocationMethod = fitType;
    duInitManagedList();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < HEAP_SIZE; ++j) {
            heap[i][j] = 0;
        }
    }

    // Initialize free list for old generation
    memoryBlockHeader* initialBlock = (memoryBlockHeader*)heap[2];
    initialBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
    initialBlock->free = 1; // Initialize as free block
    initialBlock->next = NULL;
    freeListHead[2] = initialBlock;

    // Initialize free list for young generations
    for (int i = 0; i < 2; ++i) {
        memoryBlockHeader* youngInitialBlock = (memoryBlockHeader*)heap[i];
        youngInitialBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
        youngInitialBlock->free = 1; // Initialize as free block
        youngInitialBlock->next = NULL;
        freeListHead[i] = youngInitialBlock;
    }
}

void* duMalloc(int size) {
    size = (size % 8 == 0) ? size : size + (8 - (size % 8));
    memoryBlockHeader* allocatedBlock = NULL;

    if (allocationMethod == FIRST_FIT) {
        memoryBlockHeader* currentBlock = freeListHead[currentHeap];
        memoryBlockHeader* prevBlock = NULL;

        while (currentBlock != NULL) {
            if (currentBlock->free && currentBlock->size >= size) {
                int remainingSize = currentBlock->size - size;
                if (remainingSize > (int)sizeof(memoryBlockHeader)) {
                    memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)((unsigned char*)currentBlock + sizeof(memoryBlockHeader) + size);
                    newFreeBlock->size = remainingSize - sizeof(memoryBlockHeader);
                    newFreeBlock->next = currentBlock->next;
                    newFreeBlock->free = 1;
                    if (prevBlock != NULL) {
                        prevBlock->next = newFreeBlock;
                    } else {
                        freeListHead[currentHeap] = newFreeBlock;
                    }
                    currentBlock->size = size;
                } else {
                    if (prevBlock != NULL) {
                        prevBlock->next = currentBlock->next;
                    } else {
                        freeListHead[currentHeap] = currentBlock->next;
                    }
                }
                currentBlock->free = 0; // Set the allocated block as used
                allocatedBlock = currentBlock;
                break;
            }
            prevBlock = currentBlock;
            currentBlock = currentBlock->next;
        }
    }

    return allocatedBlock ? (void*)((unsigned char*)allocatedBlock + sizeof(memoryBlockHeader)) : NULL;
}

void duFree(void* ptr) {
    if (!ptr) return;

    memoryBlockHeader* blockHeader = (memoryBlockHeader*)((unsigned char*)ptr - sizeof(memoryBlockHeader));
    blockHeader->free = 1;

    memoryBlockHeader* currentBlock = freeListHead[currentHeap];
    memoryBlockHeader* prevBlock = NULL;

    while (currentBlock != NULL && currentBlock < blockHeader) {
        prevBlock = currentBlock;
        currentBlock = currentBlock->next;
    }

    if (prevBlock != NULL) {
        prevBlock->next = blockHeader;
    } else {
        freeListHead[currentHeap] = blockHeader;
    }

    blockHeader->next = currentBlock;

    if (currentBlock != NULL && (unsigned char*)blockHeader + sizeof(memoryBlockHeader) + blockHeader->size == (unsigned char*)currentBlock && currentBlock->free) {
        blockHeader->size += currentBlock->size + sizeof(memoryBlockHeader);
        blockHeader->next = currentBlock->next;
    }

    if (prevBlock != NULL && (unsigned char*)prevBlock + sizeof(memoryBlockHeader) + prevBlock->size == (unsigned char*)blockHeader && prevBlock->free) {
        prevBlock->size += blockHeader->size + sizeof(memoryBlockHeader);
        prevBlock->next = blockHeader->next;
    }

    int managedIndex = blockHeader->managedIndex;
    managedList[managedIndex] = NULL;
}

void duMemoryDump() {
    printf("MEMORY DUMP\nCurrent heap (0/1 young): %d\n", currentHeap);
    printf("Young Heap (only the current one)\nMemory Block\n");

    memoryBlockHeader* currentBlock = (memoryBlockHeader*)heap[currentHeap];
    char graphicalString[HEAP_SIZE / 8 + 1];
    int index = 0;
    char currentChar = 'a';
    while ((unsigned char*)currentBlock < heap[currentHeap] + HEAP_SIZE) {
        printf("%s at %p, size %d\n", currentBlock->free ? "free" : "USED", (void*)currentBlock, currentBlock->size);
        for (int i = 0; i < currentBlock->size / 8; ++i) {
            graphicalString[index++] = currentBlock->free ? currentChar : currentChar - 32;
        }
        currentChar++;
        currentBlock = (memoryBlockHeader*)((unsigned char*)currentBlock + sizeof(memoryBlockHeader) + currentBlock->size);
    }
    graphicalString[index] = '\0';
    printf("%s\n", graphicalString);

    printf("Free List\n");
    currentBlock = freeListHead[currentHeap];
    while (currentBlock != NULL) {
        printf("Block at %p, size %d\n", (void*)currentBlock, currentBlock->size);
        currentBlock = currentBlock->next;
    }

    printf("Old Heap\nMemory Block\n");
    currentBlock = (memoryBlockHeader*)heap[2];
    index = 0;
    currentChar = 'A';
    while ((unsigned char*)currentBlock < heap[2] + HEAP_SIZE) {
        printf("%s at %p, size %d\n", currentBlock->free ? "free" : "USED", (void*)currentBlock, currentBlock->size);
        for (int i = 0; i < currentBlock->size / 8; ++i) {
            graphicalString[index++] = currentBlock->free ? currentChar : currentChar - 32;
        }
        currentChar++;
        currentBlock = (memoryBlockHeader*)((unsigned char*)currentBlock + sizeof(memoryBlockHeader) + currentBlock->size);
    }
    graphicalString[index] = '\0';
    printf("%s\n", graphicalString);

    printf("Free List\n");
    currentBlock = freeListHead[2];
    while (currentBlock != NULL) {
        printf("Block at %p, size %d\n", (void*)currentBlock, currentBlock->size);
        currentBlock = currentBlock->next;
    }

    printf("ManagedList\n");
    for (int i = 0; i < managedListSize; ++i) {
        printf("ManagedList[%d] = %p\n", i, managedList[i]);
    }
}



void duManagedInitMalloc(int fitType) {
    duInitMalloc(fitType);
}

void** duManagedMalloc(int size) {
    void* ptr = duMalloc(size);
    if (ptr == NULL) {
        return NULL;
    }

    int managedIndex = managedListSize;
    managedList[managedIndex] = ptr;
    memoryBlockHeader* blockHeader = (memoryBlockHeader*)((unsigned char*)ptr - sizeof(memoryBlockHeader));
    blockHeader->managedIndex = managedIndex;
    managedListSize++;

    return &managedList[managedIndex];
}

void duManagedFree(void** mptr) {
    if (mptr == NULL || *mptr == NULL) {
        return;
    }

    void* ptr = *mptr;
    *mptr = NULL;

    duFree(ptr);
}
void minorCollection() {
    int newHeap = 1 - currentHeap;
    unsigned char* newHeapBase = heap[newHeap];

    memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)newHeapBase;
    newFreeBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
    newFreeBlock->free = 1;
    newFreeBlock->next = NULL;

    unsigned char* newHeapPtr = newHeapBase;

    for (int i = 0; i < managedListSize; ++i) {
        if (managedList[i] != NULL) {
            memoryBlockHeader* oldBlock = (memoryBlockHeader*)((unsigned char*)managedList[i] - sizeof(memoryBlockHeader));
            int blockSize = oldBlock->size;
            memcpy(newHeapPtr, oldBlock, blockSize + sizeof(memoryBlockHeader));
            managedList[i] = newHeapPtr + sizeof(memoryBlockHeader);

            memoryBlockHeader* newBlock = (memoryBlockHeader*)newHeapPtr;
            newBlock->next = NULL;
            newHeapPtr += sizeof(memoryBlockHeader) + blockSize;
        }
    }

    if (newHeapPtr < newHeapBase + HEAP_SIZE) {
        memoryBlockHeader* endFreeBlock = (memoryBlockHeader*)newHeapPtr;
        endFreeBlock->size = (newHeapBase + HEAP_SIZE) - newHeapPtr - sizeof(memoryBlockHeader);
        endFreeBlock->free = 1;
        endFreeBlock->next = NULL;
        newFreeBlock->next = endFreeBlock;
    }

    freeListHead[newHeap] = newFreeBlock;
    currentHeap = newHeap;
}

void majorCollection() {
    unsigned char* newHeapBase = heap[2];
    unsigned char* newHeapPtr = newHeapBase;

    memoryBlockHeader* newFreeBlock = (memoryBlockHeader*)newHeapBase;
    newFreeBlock->size = HEAP_SIZE - sizeof(memoryBlockHeader);
    newFreeBlock->free = 1;
    newFreeBlock->next = NULL;

    for (int i = 0; i < managedListSize; ++i) {
        if (managedList[i] != NULL) {
            memoryBlockHeader* oldBlock = (memoryBlockHeader*)((unsigned char*)managedList[i] - sizeof(memoryBlockHeader));
            int blockSize = oldBlock->size;
            memcpy(newHeapPtr, oldBlock, blockSize + sizeof(memoryBlockHeader));
            managedList[i] = newHeapPtr + sizeof(memoryBlockHeader);

            memoryBlockHeader* newBlock = (memoryBlockHeader*)newHeapPtr;
            newBlock->next = NULL;
            newHeapPtr += sizeof(memoryBlockHeader) + blockSize;
        }
    }

    if (newHeapPtr < newHeapBase + HEAP_SIZE) {
        memoryBlockHeader* endFreeBlock = (memoryBlockHeader*)newHeapPtr;
        endFreeBlock->size = (newHeapBase + HEAP_SIZE) - newHeapPtr - sizeof(memoryBlockHeader);
        endFreeBlock->free = 1;
        endFreeBlock->next = NULL;
        newFreeBlock->next = endFreeBlock;
    }

    freeListHead[2] = newFreeBlock;
}
