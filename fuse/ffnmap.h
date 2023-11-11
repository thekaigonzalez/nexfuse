#ifndef FUSE_FFNMAP_H
#define FUSE_FFNMAP_H

#include "fdef.h"
#include "fctx.h"
#include "fvcpu.h"

#define FUSE_FFNMAP_INCREMENT 5 // shorter bursts than FUSE_LIST_INCREMENT

typedef struct _FFn {
  byte name;
  int (*fn) (F_Cpu *cpu, FCtx *ctx);
} FFnEntry;

typedef struct _FFnMap {
  FFnEntry *ptr;
  size_t size;
  size_t cap;
} FFnMap;

FFnMap *FFnMapInit();
void FFnMapPush(FFnMap *map, FFnEntry *fn);
void FFnMapDefine(FFnMap *map, byte name, int (*fn) (F_Cpu *cpu, FCtx *ctx));
void FFnMapFree(FFnMap *map);
FFnEntry *FFnMapGet(FFnMap *map, byte name);

#endif

