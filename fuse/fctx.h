/*Copyright 2019-2023 Kai D. Gonzalez*/

#ifndef FUSE_FCTX_H
#define FUSE_FCTX_H

// FUSE call context
// implements byte list arguments

#include "fdef.h"
#include "fmem.h"
#include "flist.h"

typedef struct FCtx {
  FList *__ptr; /* manage byte list arguments */
} FCtx;

FCtx* FCtxInit();
void* FCtxGet(FCtx *ctx, int index);
void FCtxAppend(FCtx *ctx, void *ptr);
void FCtxFree(FCtx *ctx);
void FCtxSmartFree(FCtx *ctx);
void FCtxRebuild(FCtx *ctx);

#endif
