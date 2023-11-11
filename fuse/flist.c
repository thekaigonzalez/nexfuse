#include "flist.h"
/*Copyright 2019-2023 Kai D. Gonzalez*/
FList *
FListInit ()
{
  FList *list = (FList *)malloc (sizeof (FList));

  list->size = 0;
  list->cap = FUSE_LIST_INCREMENT;
  list->ptr = malloc (list->cap * FUSE_LIST_INCREMENT);

  return list;
}

void
FListPush (FList *list, void *ptr)
{
  if (list->size == list->cap)
    {
      list->cap += FUSE_LIST_INCREMENT;
      FLRealloc (list, list->cap);
    }

  list->ptr[list->size] = ptr;

  list->size++;
}

void
FLRealloc (FList *list, size_t size)
{
  list->ptr = FRealloc (list->ptr, size * sizeof (void *));
}

void
FListFree (FList *list)
{
  FFree (list->ptr);
  FFree (list);
}

void
FListSmartFree (FList *list)
{
  for (size_t i = 0; i < list->size; i++)
    {
      FFree (list->ptr[i]);
    }

  FListFree (list);

  list->size = -1;
}

void
FListClear (FList *list)
{
  list->size = 0;
  list->cap = FUSE_LIST_INCREMENT;
  memset (list->ptr, 0, list->cap * FUSE_LIST_INCREMENT);
}

void *
FListGet (FList *list, size_t index)
{
  if (index >= list->size)
    {
      return NULL;
    }
  return list->ptr[index];
}

void *
FListPop (FList *list)
{
  void *item = FListGet (list, list->size - 1);

  list->size--;
  /// realloc

  list->ptr = FRealloc (list->ptr, list->size);

  return item;
}

byte
FLAsByte (FList *list, size_t index)
{
  return (byte) FListGet (list, index);
}

size_t
FListSize (FList *list)
{
  return list->size;
}

size_t
FListCapacity (FList *list)
{
  return list->cap;
}
