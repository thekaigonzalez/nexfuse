/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FLIST_H
#define FUSE_FLIST_H

#include "fdef.h"
#include "fmem.h"

#include <stdlib.h>
#include <string.h>

// lists of pointers to data
// allocate memory in incremental chunks defined by FUSE_LIST_INCREMENT
typedef struct FList {
  void** ptr; // pointer array
  size_t size;
  size_t cap;
} FList;

FList* FListInit(); // initializes a new FList

// adds a pointer to the list (allocates memory if needed)
void FListPush(FList* list, void* ptr);

// resizes the list
void FLRealloc(FList* list, size_t size);

// frees the list and pointer array (does not free the pointers inside the list)
void FListFree(FList* list);

// frees all the pointers (as long as they are all allocated with FMalloc)
void FListSmartFree(FList* list);

// clears the list (memset to 0)
void FListClear(FList* list);

// returns the pointer at index
void* FListGet(FList* list, size_t index);

// pop the last pointer
void* FListPop(FList* list);

// gets the array index as a byte
byte FLAsByte(FList* list, size_t index);

// returns the size of the list
size_t FListSize(FList* list);

// returns the capacity of the list
size_t FListCapacity(FList* list);

#endif
