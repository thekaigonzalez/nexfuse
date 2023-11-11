#include "fbcp.h"

int __ECHO(F_Cpu *cpu, FCtx *ctx) {
  printf("%c\n", (byte) FCtxGet(ctx, 1));
  return (0);
}

int __INITSEC(F_Cpu *cpu, FCtx *ctx) {
  printf("nd: %s\n", (char *) FCtxGet(ctx, 1));

  CPInitializeSection(cpu, (byte) FCtxGet(ctx, 2));
  return (0);
}
byte
CPRunBytecode (F_Cpu *cpu, FBytecodeChunk *chunk)
{
  int err = 0;
  int i = 0;

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

    else if (op == NNULL) {
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

      free(f);
    }
    
    else if (op == SUB && state == START) {
      state = SUBN;

      FBytecodeChunkReset(tmp);
      FListClear(_ctx->__ptr);
    }

    else if (op == ENDSUB && state == SUBN) {
      state = START;

      byte ptr = FCtxGet(_ctx, 1);

      if (!CPIsSectionInitialized(cpu, ptr)) {
        
        break;
      }

      FBytecodeChunkReset(tmp);
      FListClear(_ctx->__ptr);
    } else {
      FBytecodeChunkAppend(tmp, op);
    FListPush(_ctx->__ptr, op);
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