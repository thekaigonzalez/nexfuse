#include "fbcc.h"

FBytecodeChunk *
FBytecodeChunkInit ()
{
  FBytecodeChunk * chunk = (FBytecodeChunk *) malloc (sizeof (FBytecodeChunk));
  
  chunk->ptr = (byte *) malloc (FUSE_INITIAL_SIZE);
  chunk->size = 0;

  return chunk;
}

void
FBytecodeChunkAppend (FBytecodeChunk *chunk, byte ptr)
{
  chunk->ptr = realloc (chunk->ptr, chunk->size + 1);
  chunk->ptr [chunk->size] = ptr;
  chunk->size ++;
}

void
FBytecodeChunkMany (FBytecodeChunk *chunk, ...)
{
  va_list args;

  va_start (args, chunk);

  while (1)
   {
     byte ptr = va_arg (args, int);

     if (ptr == (byte) __END__) break;

     FBytecodeChunkAppend (chunk, ptr);
   }
}

void
FBytecodeChunkReset (FBytecodeChunk *chunk)
{
  chunk->size = 0;
  chunk->ptr = (byte *) realloc (chunk->ptr, FUSE_INITIAL_SIZE);
}

void
FBytecodeChunkFree (FBytecodeChunk *chunk)
{
  free (chunk->ptr);
  free (chunk);
}
