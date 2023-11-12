/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FVCPU_H
#define FUSE_FVCPU_H

// FUSE virtual CPU
// implements 256 registers that hold 256 bytes of data each
// also implements sections that can hold up to 256 bytes of data

#include "fdef.h"
#include "fmem.h"

typedef struct FReg
{
  byte data[FUSE_OPENLUD_REGISTER_BYTES]; // 256 bytes of data (assuming
                                          // nothing has been overwritten)
  int ptr;                                // (unused)
  int initialized; // is this register initialized
} FReg;

typedef struct FSection
{
  byte data[FUSE_OPENLUD_BYTE_TOP]; // 256 bytes of data (assuming nothing has
                                    // been overwritten)
  int ptr;
  int initialized; // is this section initialized
} FSection;

typedef struct F_Cpu
{
  FReg reg[FUSE_OPENLUD_REGISTER_LIMIT];   // 256 registers
  FSection section[FUSE_OPENLUD_BYTE_TOP]; // 256 sections
} F_Cpu;

void CPStart (F_Cpu *cpu);
FReg *CPReg (F_Cpu *cpu, int index);
FSection *CPSection (F_Cpu *cpu, int index);

void CPInitializeRegister (F_Cpu *cpu, int index);
void CPInitializeSection (F_Cpu *cpu, int index);

void CPPutByteRegister (F_Cpu *cpu, int reg, int index, byte value);
void CPPutByteSection (F_Cpu *cpu, int section, int index, byte value);

void CPAppendByteSection (F_Cpu *cpu, int section, byte value);

FBool CPIsRegisterInitialized (F_Cpu *cpu, int index);
FBool CPIsSectionInitialized (F_Cpu *cpu, int index);

byte CPGetByteRegister (F_Cpu *cpu, int reg, int index);
byte CPGetByteSection (F_Cpu *cpu, int section, int index);

void CPDisplay (F_Cpu *cpu);
void CPShowRegister (F_Cpu *cpu, int index);
void CPShowSection (F_Cpu *cpu, int index);

#endif
