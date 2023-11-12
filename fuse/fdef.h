/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FDEF_H
#define FUSE_FDEF_H

/* Bytecode version */
#define FUSE_BYTECODE_VERSION_SHORT 100L
#define FUSE_BYTECODE_VERSION "1.0.0"

// OpenLUD backward compatibility
#define FUSE_OPENLUD_BYTE_TOP 256
#define FUSE_OPENLUD_REGISTER_LIMIT FUSE_OPENLUD_BYTE_TOP // Max number of registers
#define FUSE_OPENLUD_REGISTER_BYTES FUSE_OPENLUD_BYTE_TOP // Max number of bytes in a register

// FUSE memory 
#define FUSE_LIST_INCREMENT 15
#define FUSE_INITIAL_SIZE 1

// FUSE types

// Byte (1 byte)
typedef char byte;

// boolean
typedef int FBool;

// OpenLUD ByteCode functinos
#define NNULL (byte) 00
#define ECHO (byte) 40
#define MOVE (byte) 41
#define EACH  (byte) 42
#define RESET (byte) 43
#define CLEAR (byte) 44
#define PUT (byte) 45
#define GET (byte) 46

// FUSE expansions
#define SUB (byte) 10
#define ENDSUB (byte) 11
#define IF (byte) 12
#define ENDIF (byte) 13
#define ALIAS (byte) 14
#define GOSUB (byte) 15

// initialize and end
#define INIT (byte) 100
#define INITSEC (byte) 70
#define END (byte) 22

// FUSE vararg ender
#define __END__ (byte) 255

// FUSE Error
int FError(const char* fmt);

#endif
