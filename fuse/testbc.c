/*Copyright 2019-2023 Kai D. Gonzalez*/

#include "fbcc.h"
#include "fvcpu.h"
#include "fmem.h"
#include "flist.h"
#include "fctx.h"
#include "fdef.h"
#include "ffnmap.h"
#include "fbcp.h"

main (void)
{
  F_Cpu c;
  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  FBytecodeChunkMany (chunk, 
  INITSEC, 1, NNULL,
  INIT, 1, NNULL,

  SUB, 8,
  ECHO, 0x47, NNULL,
  END,
  ENDSUB,

  SUB, 9,
  ECHO, 0x0a, NNULL,
  END,
  ENDSUB,

  GOSUB, 8, NNULL,
  GOSUB, 9, NNULL,

  END,
  __END__);

  // printf("RR %d\n", c.reg[1].data[7]);

  byte result = CPRunBytecode (&c, chunk);


  FBytecodeChunkFree (chunk);
}