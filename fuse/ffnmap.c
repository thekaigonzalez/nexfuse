#include "ffnmap.h"

FFnMap *
FFnMapInit ()
{
  FFnMap *map = (FFnMap *)FMalloc (sizeof (FFnMap));

  map->ptr = FMalloc (sizeof (FFnEntry) * FUSE_FFNMAP_INCREMENT);

  map->size = 0;

  map->cap = FUSE_FFNMAP_INCREMENT;

  return map;
}

void
FFnMapPush (FFnMap *map, FFnEntry *fn)
{
  if (map->size == map->cap)
    {
      map->cap += FUSE_FFNMAP_INCREMENT;

      map->ptr = FRealloc (map->ptr, sizeof (FFnEntry) * map->cap);
    }

  map->ptr[map->size] = *fn;

  FFree (fn);

  map->size++;
}

void
FFnMapDefine (FFnMap *map, byte name, int (*fn) (F_Cpu *cpu, FCtx *ctx))
{
  FFnEntry *_fn = (FFnEntry *)FMalloc (sizeof (FFnEntry));

  _fn->name = name;
  _fn->fn = fn;

  FFnMapPush (map, _fn);
}

void
FFnMapFree (FFnMap *map)
{
  FFree (map->ptr);
  FFree (map);
}

FFnEntry *
FFnMapGet (FFnMap *map, byte name)
{
  for (int i = 0; i < map->size; i++)
    {
      if (map->ptr[i].name == name)
        {
          return &map->ptr[i];
        }
    }
  return NULL;
}

