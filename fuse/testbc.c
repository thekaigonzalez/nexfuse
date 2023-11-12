/*Copyright 2019-2023 Kai D. Gonzalez*/

#include "fbcc.h"
#include "fvcpu.h"
#include "fmem.h"
#include "flist.h"
#include "fctx.h"
#include "fdef.h"
#include "ffnmap.h"
#include "fbcp.h"
#include "fou.h"

main (void)
{
  F_Cpu c;
  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  // FBytecodeChunkMany (chunk, 
  // INITSEC, 1, NNULL,
  // INIT, 1, NNULL,

  // SUB, 8,
  // ECHO, 0x47, NNULL,
  // END,
  // ENDSUB,

  // SUB, 9,
  // ECHO, 0x0a, NNULL,
  // END,
  // ENDSUB,

  // GOSUB, 8, NNULL,
  // GOSUB, 9, NNULL,

  // END,
  // __END__);

  FBytecodeChunkMany (chunk, 
  INIT, 1, NNULL,
  INIT, 2, NNULL,

  PUT, 1, 0x41, 7, NNULL,

  EACH, 1, NNULL,

  GET, 1, 7, 2, NNULL,

  EACH, 2, NNULL,

  END,
  __END__);

  FILE * p = fopen ("test.n", "wb");

  fwrite (chunk->ptr, 1, chunk->size, p);

  fclose (p);

  byte result = CPRunBytecode (&c, chunk);

  FBytecodeChunkFree (chunk);
}