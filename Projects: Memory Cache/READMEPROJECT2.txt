Bill Turbadrakh

I believe all my code works, except for makefile, whenever I input make, it pops up the error saying
I'm trying to call upon main.o that doesn't exist, yet everything else seems to work fine


















-------------------------------------------------------------------
-------------------------------------------------------------------
-------------------------------------------------------------------
Cache Simulator Nway Detialed Test
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Set 1
  Block 0:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Accesses:     0
Hits:         0
Misses:       0
Writebacks:   0
Miss Perc:    0
Writeback Perc: 0
-------------------------------------------------------------------
READ 0
0
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754564386
00 01 02 03 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Set 1
  Block 0:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Accesses:     1
Hits:         0
Misses:       1
Writebacks:   0
Miss Perc:    100
Writeback Perc: 0
-------------------------------------------------------------------
READ 2
2
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
00 01 02 03 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Set 1
  Block 0:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Accesses:     2
Hits:         1
Misses:       1
Writebacks:   0
Miss Perc:    50
Writeback Perc: 0
-------------------------------------------------------------------
READ 4
4
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
00 01 02 03 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
04 05 06 07 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Accesses:     3
Hits:         2
Misses:       1
Writebacks:   0
Miss Perc:    33.3333
Writeback Perc: 0
-------------------------------------------------------------------
READ 10
10
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
00 01 02 03 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
08 09 0a 0b 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
04 05 06 07 
  Block 1:
    valid: 0    tag: 0    dirty: 0    timestamp: 0
00 00 00 00 
Accesses:     4
Hits:         3
Misses:       1
Writebacks:   0
Miss Perc:    25
Writeback Perc: 0
-------------------------------------------------------------------
READ 12
12
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754696313
00 01 02 03 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
08 09 0a 0b 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
04 05 06 07 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
0c 0d 0e 0f 
Accesses:     5
Hits:         4
Misses:       1
Writebacks:   0
Miss Perc:    20
Writeback Perc: 0
-------------------------------------------------------------------
READ 1
1
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346754969939
08 09 0a 0b 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
04 05 06 07 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
0c 0d 0e 0f 
Accesses:     6
Hits:         5
Misses:       1
Writebacks:   0
Miss Perc:    16.6667
Writeback Perc: 0
-------------------------------------------------------------------
READ 16
16
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
10 11 12 13 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346754833785
04 05 06 07 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
0c 0d 0e 0f 
Accesses:     7
Hits:         6
Misses:       1
Writebacks:   0
Miss Perc:    14.2857
Writeback Perc: 0
-------------------------------------------------------------------
WRITE 6
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
10 11 12 13 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 1    timestamp: 1718305346755564557
04 05 66 07 
  Block 1:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755120872
0c 0d 0e 0f 
Accesses:     7
Hits:         6
Misses:       1
Writebacks:   1
Miss Perc:    14.2857
Writeback Perc: 12.5
-------------------------------------------------------------------
WRITE 21
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
10 11 12 13 
Set 1
  Block 0:
    valid: 1    tag: 0    dirty: 1    timestamp: 1718305346755564557
04 05 66 07 
  Block 1:
    valid: 1    tag: 2    dirty: 1    timestamp: 1718305346755712464
14 55 16 17 
Accesses:     7
Hits:         6
Misses:       1
Writebacks:   2
Miss Perc:    14.2857
Writeback Perc: 22.2222
-------------------------------------------------------------------
READ 12
04 05 66 07 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
10 11 12 13 
Set 1
  Block 0:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755851476
0c 0d 0e 0f 
  Block 1:
    valid: 1    tag: 2    dirty: 1    timestamp: 1718305346755712464
14 55 16 17 
Accesses:     8
Hits:         7
Misses:       1
Writebacks:   2
Miss Perc:    12.5
Writeback Perc: 20
-------------------------------------------------------------------
WRITE 30
04 05 66 07 04 05 06 07 14 55 16 17 0c 0d 0e 0f 
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
Set 0
  Block 0:
    valid: 1    tag: 0    dirty: 0    timestamp: 1718305346755269384
00 01 02 03 
  Block 1:
    valid: 1    tag: 2    dirty: 0    timestamp: 1718305346755416382
10 11 12 13 
Set 1
  Block 0:
    valid: 1    tag: 1    dirty: 0    timestamp: 1718305346755851476
0c 0d 0e 0f 
  Block 1:
    valid: 1    tag: 3    dirty: 1    timestamp: 1718305346755997944
1c 1d ee 1f 
Accesses:     8
Hits:         7
Misses:       1
Writebacks:   3
Miss Perc:    12.5
Writeback Perc: 27.2727