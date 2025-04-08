#ifndef DUMALLOC_H
#define DUMALLOC_H

void duMemoryDump();
void minorCollection();
void majorCollection(); // Added function prototype

#define FIRST_FIT 0
#define BEST_FIT 1

void duManagedInitMalloc(int fitType);
void** duManagedMalloc(int size);
void duManagedFree(void** mptr);

#define Managed(p) (*p)
#define Managed_t(t) t*

#endif