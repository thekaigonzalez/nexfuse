#include "fbcc.h"
#include "fbcp.h"
#include "fctx.h"
#include "flist.h"
#include "fvcpu.h"

#include <stdio.h>
#include <assert.h>

#define PASSED printf ("test %s passed\n", __func__)

test_list_cap (void)
{
  FList *list = FListInit ();

  int i;
  for (i = 0; i < 50; i++)
    {
      FListPush (list, (int *)i);
      printf ("cap: %d, size: %d\n", (int)list->cap, (int)list->size);
    }

  for (i = 0; i < list->size; i++)
    printf ("%d\n", (int)list->ptr[i]);

  FListFree (
      list); // if all pointers are allocated with FMalloc, this frees them

  PASSED;
}

test_ctx (void)
{
  FCtx *ctx = FCtxInit ();

  FCtxAppend (ctx, "hello");

  printf ("%s\n", (char *)FListPop (ctx->__ptr));

  FCtxFree (ctx);

  PASSED;
}

test_vcpu_reg (void)
{
  F_Cpu cpu;

  CPStart (&cpu);

  FReg *reg = CPReg (&cpu, 0);

  reg->data[0] = 1;

  CPShowRegister (&cpu, 0);

  PASSED;
}

test_openlud_example_in_c (void)
{
  F_Cpu c;

  CPInitializeRegister (&c, 1);
  CPInitializeRegister (&c, 2);

  CPPutByteRegister (&c, 1, 7, 0x41);

  for (int i = 0; i < 256; i++)
    {
      if (CPGetByteRegister (&c, 1, i) != 0)
        printf ("%c", CPGetByteRegister (&c, 1, i));
    }

  printf ("\n");

  CPPutByteRegister (&c, 2, 0, CPGetByteRegister (&c, 1, 7));

  for (int i = 0; i < 256; i++)
    {
      if (CPGetByteRegister (&c, 2, i) != 0)
        printf ("%c", CPGetByteRegister (&c, 2, i));
    }

  printf ("\n");
  PASSED;
}

test_bytecode_list_singular (void)
{
  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  FBytecodeChunkAppend (chunk, 10);
  FBytecodeChunkAppend (chunk, 5);
  FBytecodeChunkAppend (chunk, 7);
  FBytecodeChunkAppend (chunk, 3);

  for (int i = 0; i < chunk->size; i++)
    {
      printf ("byte: %d\n", chunk->ptr[i]);
    }

  FBytecodeChunkFree (chunk);

  PASSED;
}

test_bytecode_list_many (void)
{
  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  FBytecodeChunkMany (chunk, 10, 5, 7, 3, END);

  for (int i = 0; i < chunk->size; i++)
    {
      printf ("byte: %d\n", chunk->ptr[i]);
    }

  FBytecodeChunkFree (chunk);

  PASSED;
}

test_bytecode_executor (void)
{
  F_Cpu c;
  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  FBytecodeChunkMany (chunk, 
  
  INITSEC, 1, NNULL,
  INIT, 1, NNULL,

  PUT, 1, 0x47, 7, NNULL,
  EACH, 1, NNULL,

  __END__);

  // printf("RR %d\n", c.reg[1].data[7]);

  CPShowRegister(&c, 1);

  byte result = CPRunBytecode (&c, chunk);

  FBytecodeChunkFree (chunk);

  PASSED;
}

int sample_function (F_Cpu *cpu, FCtx *ctx)
{
  printf ("Hello, World!\n");
  return (0);
}

test_function_mapping (void) {
  FFnMap *map = FFnMapInit ();

  FFnMapDefine (map, 100, sample_function);
  
  FFnEntry *sf = FFnMapGet (map, 100);

  if (sf == NULL)
    {
      printf("function not found\n");
      return;
    }
  
  FFnMapFree (map);
}

test_dangling_pointer_endurance (void)
{
  FCtx *c = FCtxInit ();

  FCtxRebuild (c);
  FCtxRebuild (c);
  FCtxRebuild (c);
  FCtxRebuild (c);

  FCtxFree (c);

  PASSED;
}

main ()
{
  test_list_cap ();
  test_ctx ();
  test_vcpu_reg ();
  test_openlud_example_in_c ();
  test_bytecode_list_singular ();
  test_bytecode_list_many ();
  test_bytecode_executor ();
  test_dangling_pointer_endurance ();
  test_function_mapping();
}
