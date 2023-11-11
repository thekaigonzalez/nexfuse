/*Copyright 2019-2023 Kai D. Gonzalez*/

// define functions for proper memory management and pointer tracking

#ifndef FUSE_FMEM_H
#define FUSE_FMEM_H

#include "fdef.h"

#include <stdlib.h>

#define FMalloc(size) malloc(size)
#define FRealloc(ptr, size) realloc(ptr, size)
#define FFree(ptr) free(ptr)

#endif
