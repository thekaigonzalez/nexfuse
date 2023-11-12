#include "fdef.h"

#include <stdio.h>

int
FError (const char *fmt)
{
  fprintf (stderr, "fuse: error: %s\n", fmt);  
  return 0;
}