#include "fctx.h"
/*Copyright 2019-2023 Kai D. Gonzalez*/
FCtx *
FCtxInit ()
{
  FCtx *ctx = (FCtx *) malloc (sizeof (FCtx));

  ctx->__ptr = FListInit ();

  return ctx;
}

void *
FCtxGet (FCtx *ctx, int index)
{
  if (index < 0 || index >= ctx->__ptr->size) {
    return NULL;
  }
  return FListGet (ctx->__ptr, index);
}

void
FCtxAppend (FCtx *ctx, void *ptr)
{
  FListPush (ctx->__ptr, ptr);
}

void
FCtxFree (FCtx *ctx)
{
  FListFree (ctx->__ptr);
  FFree(ctx);
}

void
FCtxSmartFree (FCtx *ctx)
{
  FListSmartFree (ctx->__ptr);
  FFree(ctx);
}

void
FCtxRebuild (FCtx *ctx)
{
  FListClear (ctx->__ptr);
}
