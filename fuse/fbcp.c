#include "fbcp.h"

int
__ECHO (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 1)
    {
      return -1;
    }
  printf ("%c", (byte)FCtxGet (ctx, 1));
  return (0);
}

int
__INITSEC (F_Cpu *cpu, FCtx *ctx)
{
  CPInitializeSection (cpu, (byte)FCtxGet (ctx, 1)); // initialize the section
  return (0);
}

int
__INIT (F_Cpu *c, FCtx *ctx)
{
  if (ctx->__ptr->size < 2)
    {
      return -1;
    }

  CPInitializeRegister (c, (byte)FCtxGet (ctx, 1));
  return (0);
}

// PUT [reg] [byte] [pos]
int
__PUT (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 4)
    {
      return -1;
    }
  byte reg_num = (byte)FCtxGet (ctx, 1);
  byte reg_byte = (byte)FCtxGet (ctx, 2);
  byte reg_pos = (byte)FCtxGet (ctx, 3);

  // printf("put byte %d in register %d at position %d\n", reg_byte, reg_num,
  // reg_pos);

  FReg *r = &cpu->reg[reg_num];

  r->data[reg_pos] = reg_byte;

  return (0);
}

// EACH [reg]
int
__EACH (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 2)
    {
      return -1;
    }
  byte reg_num = (byte)FCtxGet (ctx, 1);

  FReg reg = cpu->reg[reg_num];

  for (int i = 0; i < FUSE_OPENLUD_REGISTER_BYTES; ++i)
    {
      if (reg.data[i] != 0)
        {
          printf ("%c", reg.data[i]);
        }
    }
  return 0;
}

// RESET [reg]
int
__RESET (F_Cpu *cpu, FCtx *ctx)
{
  byte reg_num = (byte)FCtxGet (ctx, 1);
  FReg *reg = &cpu->reg[reg_num];
  memset (reg->data, 0, FUSE_OPENLUD_REGISTER_BYTES);
  return 0;
}

int
__GOSUB (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 2)
    {
      return -1;
    }

  byte reg_num = (byte)FCtxGet (ctx, 1);

  if (reg_num >= FUSE_OPENLUD_REGISTER_LIMIT)
    {
      printf ("error: invalid register number %d\n", reg_num);
      return -1;
    }

  FSection *reg = &cpu->section[reg_num];

  FBytecodeChunk *tmp = FBytecodeChunkInit ();

  if (reg == NULL)
    {
      return -1;
    }

  for (int i = 0; i < reg->ptr; ++i)
    {
      FBytecodeChunkAppend (tmp, reg->data[i]);
    }

  CPRunBytecode (cpu, tmp);

  FBytecodeChunkFree (tmp);
  return 0;
}

int
__CLEAR (F_Cpu *cpu, FCtx *ctx)
{
  // clear all registers
  for (int i = 0; i < FUSE_OPENLUD_REGISTER_LIMIT; i++)
    {
      memset (&cpu->reg[i].data, 0, FUSE_OPENLUD_REGISTER_BYTES);
    }
}

// __GET
// get byte in reg at pos and put in reg OUTREG
int
__GET (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 4)
    {
      return -1;
    }
  byte reg_num = (byte)FCtxGet (ctx, 1);
  byte reg_pos = (byte)FCtxGet (ctx, 2);
  byte reg_out = (byte)FCtxGet (ctx, 3);

  FReg *r = &cpu->reg[reg_num];

  FReg *n = &cpu->reg[reg_out];
  n->data[n->ptr] = r->data[reg_pos];
  n->ptr++;

  return (0);
}

// __MOVE
// moves a byte into a register
int
__MOVE (F_Cpu *cpu, FCtx *ctx)
{
  byte reg_num = (byte)FCtxGet (ctx, 1);
  byte reg_byte = (byte)FCtxGet (ctx, 2);

  if (reg_num >= FUSE_OPENLUD_REGISTER_LIMIT)
    {
      printf ("Error 1\n");
      return -1;
    }

  if (reg_byte >= FUSE_OPENLUD_REGISTER_BYTES)
    {
      printf ("%d\n", reg_byte);
      printf ("Error 2\n");

      return -1;
    }

  FReg *r = &cpu->reg[reg_num];

  r->data[r->ptr] = reg_byte;
  r->ptr++;

  return (0);
}

// __ADD
// takes all bytes in REG1 and adds them to REG2
int
__ADD (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 3)
    {
      printf ("add: not enough arguments\n");
      return -1;
    }

  byte reg_num1 = (byte)FCtxGet (ctx, 1);
  byte reg_num2 = (byte)FCtxGet (ctx, 2);

  FReg *r1 = &cpu->reg[reg_num1];
  FBigReg *r2 = &cpu->bigreg[reg_num2];

  int result = 0;

  for (int i = 0; i < FUSE_OPENLUD_REGISTER_BYTES; ++i)
    {
      result += r1->data[i];
    }

  r2->data[r2->ptr] = (byte)result;
  r2->ptr++;

  return (0);
}

// __DB
// prints out values in a big register if it's not 0
int
__DB (F_Cpu *cpu, FCtx *ctx)
{
  if (ctx->__ptr->size < 2)
    {
      return -1;
    }

  byte reg_num = (byte)FCtxGet (ctx, 1);

  FBigReg *r = &cpu->bigreg[reg_num];

  if (r->ptr == 0)
    {
      return -1;
    }

  for (int i = 0; i < r->ptr; ++i)
    {
      printf ("%d ", r->data[i]);
    }
  return (0);
}

byte
CPRunBytecode (F_Cpu *cpu, FBytecodeChunk *chunk)
{
  int err = 0;
  int i = 0;

  int pc = 0; // keep count of current place

  FFnMap *fns = FFnMapInit ();

  FFnMapDefine (fns, ECHO, __ECHO);
  FFnMapDefine (fns, INITSEC, __INITSEC);
  FFnMapDefine (fns, EACH, __EACH);
  FFnMapDefine (fns, PUT, __PUT);
  FFnMapDefine (fns, INIT, __INIT);
  FFnMapDefine (fns, RESET, __RESET);
  FFnMapDefine (fns, CLEAR, __CLEAR);
  FFnMapDefine (fns, GOSUB, __GOSUB);
  FFnMapDefine (fns, GET, __GET);
  FFnMapDefine (fns, MOVE, __MOVE);
  FFnMapDefine (fns, ADD, __ADD);
  FFnMapDefine (fns, LAR, __DB);

  /*math*/

  _FBytecodeState state = START;

  FBytecodeChunk *tmp = FBytecodeChunkInit ();
  FCtx *_ctx = FCtxInit ();

  int end = 0;

  while (1)
    {

      if (i >= chunk->ptr)
        {
          printf ("fuse: infinite diffusion near (%p) (are you missing an "
                  "END?) => %d\n",
                  &chunk->ptr[i], chunk->ptr[i]);
          printf ("[C]: walk: %d\n", pc);
          break;
        }

      byte op = chunk->ptr[i];

      if (op == END && state == START && pc == 0)
        {
          end = 1;
          break; // END signals end of bytecode
        }

      if (op == SUB && pc == 0 && state == START)
        {
          state = SUBN;
        }

      else if (op == ENDSUB && state == SUBN)
        {
          state = START;

          byte reg_addr = (byte)FCtxGet (_ctx, 0);
          FSection *sector = &cpu->section[reg_addr];

          CPInitializeSection (cpu, reg_addr);

          for (int j = 1; j < _ctx->__ptr->size; ++j)
            {
              CPAppendByteSection (cpu, reg_addr, _ctx->__ptr->ptr[j]);
            }

          pc = 0;

          FBytecodeChunkReset (tmp);
          FListClear (_ctx->__ptr);
        }

      else if (op == NNULL && pc > 0 && state == START)
        { /* if the pc is greater than 0 meaning that we've advanced*/
          if ((byte)FCtxGet (_ctx, 0) == NNULL)
            {
              // ignore this, an excessive NNULL
            }
          else
            {
              FFnEntry *f = FFnMapGet (fns, (byte)FCtxGet (_ctx, 0));

              if (f == NULL)
                {
                  printf (
                      "fuse: unknown function call near (%p) => %d\nuseful "
                      "information:\n\t*pc -> %d\n",
                      &op, tmp->ptr[0], pc);
                  err = 1;
                  break;
                }

              if (f->fn (cpu, _ctx) != 0)
                {
                  printf ("fuse: error: %d\n", tmp->ptr[0]);
                  err = 1;
                  break;
                }

              FBytecodeChunkReset (tmp);
              FListClear (_ctx->__ptr);

              pc = 0;
            }
        }
      else
        {
          FBytecodeChunkAppend (tmp, op);
          FListPush (_ctx->__ptr, op);
          pc++;
        }

      i++;
    }

  if (state != START)
    {
      printf ("fuse: premature end of bytecode near (%p) => %d\n",
              &tmp->ptr[0], tmp->ptr[0]);
    }

  FBytecodeChunkFree (tmp);
  FCtxFree (_ctx);
  FFnMapFree (fns);

  if (err)
    {
      printf ("too many errors, aborting\n");
      return (byte)-1;
    }

  return (byte)0;
}
