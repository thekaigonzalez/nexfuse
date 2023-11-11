#include "fbcp.h"

int __ECHO(F_Cpu *cpu, FCtx *ctx) {
  printf("%c\n", (byte) FCtxGet(ctx, 1));
  return (0);
}

int __INITSEC(F_Cpu *cpu, FCtx *ctx) {
  printf("nd: %s\n", (char *) FCtxGet(ctx, 1));

  CPInitializeSection(cpu, (byte) FCtxGet(ctx, 1));
  return (0);
}
byte
CPRunBytecode (F_Cpu *cpu, FBytecodeChunk *chunk)
{
  int err = 0;
  int i = 0;

  int pc = 0; // keep count of current place

  FFnMap *fns = FFnMapInit();

  FFnMapDefine(fns, ECHO, __ECHO);
  FFnMapDefine(fns, INITSEC, __INITSEC);

  _FBytecodeState state = START;

  FBytecodeChunk *tmp = FBytecodeChunkInit();
  FCtx *_ctx = FCtxInit();

  while (1) {
    
    if (i >= chunk->size) {
      break;
    }

    byte op = chunk->ptr[i];

    if (op == END && state == START) {
      break; // END signals end of bytecode
    }

    else if (op == NNULL && pc > 0) { /* if the pc is greater than 0 meaning that we've advanced*/
      FFnEntry *f = FFnMapGet(fns, FCtxGet(_ctx, 0));

      if (f == NULL) {
        printf("Unknown function: %d\n", tmp->ptr[0]);
        err = 1;
        break;
      }

      if (f->fn(cpu, _ctx) != 0) {
        printf("Function error: %d\n", tmp->ptr[0]);
        err = 1;
        break;
      }

      FBytecodeChunkReset(tmp);
      FListClear(_ctx->__ptr);

      pc = 0;
    } else {
      FBytecodeChunkAppend(tmp, op);
      FListPush(_ctx->__ptr, op);
      pc++;
    }

    i++;
  }

  FBytecodeChunkFree(tmp);
  FCtxFree(_ctx);
  FFnMapFree(fns);

  if (err) {
    printf("too many errors, aborting\n");
    return (byte) -1;
  }

  return (byte) 0;
}