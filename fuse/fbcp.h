/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FBCP_H
#define FUSE_FBCP_H

// FUSE byte code parser

#include "fdef.h"  // FUSE definitions
#include "fvcpu.h" // FUSE virtual CPU
#include "flist.h" // FUSE list
#include "fmem.h"  // FUSE memory
#include "fctx.h"  // FUSE context
#include "fbcc.h"  // FUSE bytecode
#include "ffnmap.h" // FUSE function map

#include <stdio.h>

typedef enum _FBytecodeState
{
  START, // start
  SUBN, // subroutine
  IFN, // if statement
  ENDOF, // end of bytecode
} _FBytecodeState;

typedef void (*FBytecodeFunction) (F_Cpu *cpu, FCtx *ctx);

byte CPRunBytecode (F_Cpu *cpu, FBytecodeChunk *chunk);

#endif
