/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FBCC_H
#define FUSE_FBCC_H

// defines simple bytecode list types
#include "fdef.h"

#include <stdarg.h>
#include <stdlib.h>

typedef struct _FBytecodeChunk {
  byte *ptr;
  size_t size;
} FBytecodeChunk;

// FUSE bytecode function

FBytecodeChunk *FBytecodeChunkInit();
void FBytecodeChunkAppend(FBytecodeChunk *chunk, byte ptr);
void FBytecodeChunkMany(FBytecodeChunk *chunk, ...);
void FBytecodeChunkReset(FBytecodeChunk *chunk);
void FBytecodeChunkFree(FBytecodeChunk *chunk);

#endif
