// Simple C++ version of Cache Memory Simulator
// All classes are used like Java does their classes
// Arrays (not Vectors) are the only data structure and they
//   only hold pointers to objects rather than the objects themselves
// No operator overloading, inheritance, or objects on the runtime stack
// Basically, it is as simple a C++ setup as possible

#include <stdio.h>
#include "Memory.h"
#include "Cache.h"

void testNwayDetail() {
  // This is a test the test an N-way associative cache
  // It is a full test that will test all the features of the cache
  // First reading Misses and Hits
  // Then LRU replacement policy
  // Then writes that are hits and misses
  // Then reads/writes that have to do writebacks

  // It is meant to make sure the code is working correctly
  // It is not meant to be a performance test
  printf("-------------------------------------------------------------------\n");
  printf("-------------------------------------------------------------------\n");
  printf("-------------------------------------------------------------------\n");
  
  printf("Cache Simulator Nway Detialed Test\n");

  // My main memory has 32 bytes
  Memory* m = new Memory(32);

  // Cache with 16 bytes, 4 bytes per block, 2-way associative
  Cache* c = new Cache(m, 16, 4, 2);
 
  m->display();
  c->display();

  // First check that the reads work
  // The first read is always a miss
  // Miss in set 0
  printf("-------------------------------------------------------------------\n");
  printf("READ 0\n");
  printf("%d\n", c->read(0));
  m->display();
  c->display();

  // Next check a cache hit
  // Hit in set 0
  printf("-------------------------------------------------------------------\n");
  printf("READ 2\n");
  printf("%d\n", c->read(2));
  m->display();
  c->display();

  // Now do 3 more reads to fill up the cache
  // This is read miss one
  // Miss in set 1
  printf("-------------------------------------------------------------------\n");
  printf("READ 4\n");
  printf("%d\n", c->read(4));
  m->display();
  c->display();

  // This is read miss two
  // This also checks that it will read in the block
  //   starting at 8 rather than 10 since 8-11 includes 10
  // Miss in set 0
  printf("-------------------------------------------------------------------\n");
  printf("READ 10\n");
  printf("%d\n", c->read(10));
  m->display();
  c->display();

  // This is read miss three
  // Miss in set 1
  printf("-------------------------------------------------------------------\n");
  printf("READ 12\n");
  printf("%d\n", c->read(12));
  m->display();
  c->display();

  // At this point both blocks are filled in both sets
  // So the next miss will have to replace a block

  // This is to change the LRU block in set 0 from block 0 to block 1
  // It will impact what happens in the next read below
  printf("-------------------------------------------------------------------\n");
  printf("READ 1\n");
  printf("%d\n", c->read(1));
  m->display();
  c->display();

  // This replaces the block at 1 of set 0 since it is LRU
  printf("-------------------------------------------------------------------\n");
  printf("READ 16\n");
  printf("%d\n", c->read(16));
  m->display();
  c->display();


  // Now check that the writes work

  // First write to something that is already in the cache
  // This should change the value from 0x06 to 0x66
  // This should also mark the block as dirty
  printf("-------------------------------------------------------------------\n");
  printf("WRITE 6\n");
  c->write(6, 0x66);
  m->display();
  c->display();

  // Next write to something that is not in the cache and has 
  //   to be loaded but the evicted is not dirty
  // Should load in the block starting at 20
  // Should replace the block at 1 of set 1 (since it is LRU)
  // Should change the value from 0x15 to 0x55
  printf("-------------------------------------------------------------------\n");
  printf("WRITE 21\n");
  c->write(21, 0x55);
  m->display();
  c->display();

  // Finally write to something that is no in the cache and has
  //   to be loaded and the evicted block is dirty
  // Note that at this point both blocks in set 1 are dirty
  //   so any read or write that loads into set 1 will evict a dirty block
  
  // We will do a read first that does a writeback
  // This should evict block 0 of set 1
  printf("-------------------------------------------------------------------\n");
  printf("READ 12\n");
  c->read(12);
  m->display();
  c->display();


  // And finally a write that does a writeback
  // This should evict block 1 of set 1 since it is now LRU
  // Changes 1e to ee
  printf("-------------------------------------------------------------------\n");
  printf("WRITE 30\n");
  c->write(30, 0xEE);
  m->display();
  c->display();


  // Note that when it is complete there is still a dirty block
  // We could write it back to the memory at this point
  // But since the program is about to end, memory will be not
  //   used again so there is no need to writeback the cache to it
}

int main() {

  // Correctness test
  testNwayDetail();

  // Performance tests go here...

//   -------------------------------------------------------------------
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// Cache Simulator Nway Detialed Test
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Set 1
//   Block 0:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Accesses:     0
// Hits:         0
// Misses:       0
// Writebacks:   0
// Miss Perc:    0
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 0
// 0
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754564386
// 00 01 02 03 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Set 1
//   Block 0:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Accesses:     1
// Hits:         0
// Misses:       1
// Writebacks:   0
// Miss Perc:    100
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 2
// 2
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
// 00 01 02 03 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Set 1
//   Block 0:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Accesses:     2
// Hits:         1
// Misses:       1
// Writebacks:   0
// Miss Perc:    50
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 4
// 4
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
// 00 01 02 03 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
// 04 05 06 07 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Accesses:     3
// Hits:         2
// Misses:       1
// Writebacks:   0
// Miss Perc:    33.3333
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 10
// 10
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
// 08 09 0a 0b 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
// 04 05 06 07 
//   Block 1:
//     valid: 0    tag: 0    dirty: 0    timestamp: 0
// 00 00 00 00 
// Accesses:     4
// Hits:         3
// Misses:       1
// Writebacks:   0
// Miss Perc:    25
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 12
// 12
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
// 08 09 0a 0b 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
// 04 05 06 07 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
// 0c 0d 0e 0f 
// Accesses:     5
// Hits:         4
// Misses:       1
// Writebacks:   0
// Miss Perc:    20
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 1
// 1
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
// 08 09 0a 0b 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
// 04 05 06 07 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
// 0c 0d 0e 0f 
// Accesses:     6
// Hits:         5
// Misses:       1
// Writebacks:   0
// Miss Perc:    16.6667
// Writeback Perc: 0
// -------------------------------------------------------------------
// READ 16
// 16
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
// 10 11 12 13 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
// 04 05 06 07 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
// 0c 0d 0e 0f 
// Accesses:     7
// Hits:         6
// Misses:       1
// Writebacks:   0
// Miss Perc:    14.2857
// Writeback Perc: 0
// -------------------------------------------------------------------
// WRITE 6
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
// 10 11 12 13 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 1    timestamp: 1718305346755564557
// 04 05 66 07 
//   Block 1:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
// 0c 0d 0e 0f 
// Accesses:     7
// Hits:         6
// Misses:       1
// Writebacks:   1
// Miss Perc:    14.2857
// Writeback Perc: 12.5
// -------------------------------------------------------------------
// WRITE 21
// 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
// 10 11 12 13 
// Set 1
//   Block 0:
//     valid: 1    tag: 0    dirty: 1    timestamp: 1718305346755564557
// 04 05 66 07 
//   Block 1:
//     valid: 1    tag: 2    dirty: 1    timestamp: 1718305346755712464
// 14 55 16 17 
// Accesses:     7
// Hits:         6
// Misses:       1
// Writebacks:   2
// Miss Perc:    14.2857
// Writeback Perc: 22.2222
// -------------------------------------------------------------------
// READ 12
// 04 05 66 07 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
// 10 11 12 13 
// Set 1
//   Block 0:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755851476
// 0c 0d 0e 0f 
//   Block 1:
//     valid: 1    tag: 2    dirty: 1    timestamp: 1718305346755712464
// 14 55 16 17 
// Accesses:     8
// Hits:         7
// Misses:       1
// Writebacks:   2
// Miss Perc:    12.5
// Writeback Perc: 20
// -------------------------------------------------------------------
// WRITE 30
// 04 05 66 07 04 05 06 07 14 55 16 17 0c 0d 0e 0f 
// 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
// Set 0
//   Block 0:
//     valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
// 00 01 02 03 
//   Block 1:
//     valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
// 10 11 12 13 
// Set 1
//   Block 0:
//     valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755851476
// 0c 0d 0e 0f 
//   Block 1:
//     valid: 1    tag: 3    dirty: 1    timestamp: 1718305346755997944
// 1c 1d ee 1f 
// Accesses:     8
// Hits:         7
// Misses:       1
// Writebacks:   3
// Miss Perc:    12.5
// Writeback Perc: 27.2727


}
