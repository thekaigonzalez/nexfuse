#include "fvcpu.h"

#include <string.h>
#include <stdio.h>

void
CPStart (F_Cpu *cpu)
{
  // set all registers/sections values to 0

  for (int i = 0; i < FUSE_OPENLUD_REGISTER_LIMIT; i++) {
    memset (&cpu->reg[i].data, 0, FUSE_OPENLUD_REGISTER_BYTES);
    memset (&cpu->section[i].data, 0, FUSE_OPENLUD_BYTE_TOP);

    cpu->reg[i].ptr = 0;
    cpu->section[i].ptr = 0;
  }
}

FReg *
CPReg (F_Cpu *cpu, int index)
{
  return &cpu->reg[index];
}

FSection *
CPSection (F_Cpu *cpu, int index)
{
  return &cpu->section[index];
}

void
CPInitializeRegister (F_Cpu *cpu, int index)
{
  memset (&cpu->reg[index].data, 0, FUSE_OPENLUD_REGISTER_BYTES);
  cpu->reg[index].initialized = 0;
}

void
CPInitializeSection (F_Cpu *cpu, int index)
{
  memset (&cpu->section[index].data, 0, FUSE_OPENLUD_BYTE_TOP);
  cpu->section[index].initialized = 0;
}

void
CPPutByteRegister (F_Cpu *cpu, int reg, int index, byte value)
{
  cpu->reg[reg].data[index] = value;
}

void
CPPutByteSection (F_Cpu *cpu, int section, int index, byte value)
{
  cpu->section[section].data[index] = value;
}

void
CPAppendByteSection (F_Cpu *cpu, int section, byte value)
{
  cpu->section[section].data[cpu->section[section].ptr] = value;
  cpu->section[section].ptr++;
}

int
CPVerifySection (F_Cpu *cpu, int index)
{
  if (index < 0 || index >= FUSE_OPENLUD_REGISTER_LIMIT) {
    return -1;
  }

  if (!cpu->section[index].initialized) {
    return -1;
  }

  if (cpu->section[index].ptr > FUSE_OPENLUD_BYTE_TOP) {
    return -1;
  }

  return 0;
}

int
CPVerifyRegister (F_Cpu *cpu, int index)
{
  if (index < 0 || index >= FUSE_OPENLUD_REGISTER_LIMIT) {
    return -1;
  }

  if (!cpu->reg[index].initialized) {
    return -1;
  }

  if (cpu->reg[index].ptr > FUSE_OPENLUD_REGISTER_BYTES) {
    return -1;
  }

  return 0;
}

FBool
CPIsRegisterInitialized (F_Cpu *cpu, int index)
{
  return cpu->reg[index].initialized;
}

FBool
CPIsSectionInitialized (F_Cpu *cpu, int index)
{
  return cpu->section[index].initialized;
}

byte
CPGetByteRegister (F_Cpu *cpu, int reg, int index)
{
  return cpu->reg[reg].data[index];
}

byte
CPGetByteSection (F_Cpu *cpu, int section, int index)
{
  return cpu->section[section].data[index];
}

void
CPDisplay (F_Cpu *cpu)
{
  for (int i = 0; i < FUSE_OPENLUD_REGISTER_LIMIT; i++) {
    printf ("reg %d: %d\n", i, cpu->reg[i].ptr);
    printf ("section %d: %d\n", i, cpu->section[i].ptr);

    for (int j = 0; j < FUSE_OPENLUD_BYTE_TOP; j++) {
      printf ("%d ", cpu->section[i].data[j]);
    }

    for (int j = 0; j < FUSE_OPENLUD_BYTE_TOP; j++) {
      printf ("%d ", cpu->reg[i].data[j]);
    }


    printf ("\n");
  }
}

void
CPShowRegister (F_Cpu *cpu, int index)
{
  printf ("reg %d: %d\n", index, cpu->reg[index].ptr);

  for (int j = 0; j < FUSE_OPENLUD_BYTE_TOP; j++) {
    printf ("%d ", cpu->reg[index].data[j]);
  }

  printf ("\n");
}

void
CPShowSection (F_Cpu *cpu, int index)
{
  printf ("section %d: %d\n", index, cpu->section[index].ptr);

  for (int j = 0; j < FUSE_OPENLUD_BYTE_TOP; j++) {
    printf ("%d ", cpu->section[index].data[j]);
  }

  printf ("\n");
}
