#include "fuse.h"

int
FMain (int argc, char *argv[])
{
  if (argc < 2) {
    printf("usage: %s <file>\n", argv[0]);
    return 1;
  }

  F_Cpu c;

  FBytecodeChunk *chunk = FBytecodeChunkInit ();

  if (chunk == NULL) {
    printf("fuse: error: failed to initialize bytecode chunk\n");
    FFree(chunk);
    return 1;
  }

  char* file = argv[1];

  FILE *f = fopen(file, "rb");
  if (f == NULL) {
    printf("fuse: error: failed to open file `%s'\n", file);
    FBytecodeChunkFree(chunk);
    return 1;
  }

  byte b;
  while (fread(&b, 1, 1, f) == 1) {
    FBytecodeChunkAppend(chunk, b);
  }

  CPRunBytecode(&c, chunk);

  fclose(f);
  FBytecodeChunkFree(chunk);

  return 0;
}

int main(int argc, char *argv[])
{
  return FMain (argc, argv);
}
