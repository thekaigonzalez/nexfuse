#include "fou.h"

void
FPrintBytecodeChunk (FBytecodeChunk *chunk)
{
  if (chunk == NULL)
    {
      printf ("NULL");
      return;
    }

  printf ("ptr: %p, size: %ld\n", chunk->ptr, chunk->size);

  for (int i = 0; i < chunk->size; i++)
    {
      byte op = chunk->ptr[i];

      if (op == NNULL)
        {
          printf ("NULL\n");
        }
      else if (op == SUB) {
        printf("SUB %d\n", chunk->ptr[i + 1]);
      }

      else if (op == ENDSUB) {
        printf("ENDSUB\n");
      }

      else if (op == END) {
        printf("END\n");
      }
      else
        {
          switch (op)
            {
            case INITSEC:
              printf ("INITSEC ");
              break;
            case INIT:
              printf ("INIT ");
              break;
            case ENDSUB:
              printf ("ENDSUB ");
              break;
            case ECHO:
              printf ("ECHO ");
              break;
            case GOSUB:
              printf ("GOSUB ");
              break;
            case MOVE:
              printf ("MOVE ");
              break;
            case END:
              printf ("END ");
              break;
            case SUB:
              printf ("SUB ");
              break;
            case GET:
              printf ("GET ");
              break;
            case PUT:
              printf ("PUT ");
              break;
            case CLEAR:
              printf ("CLEAR ");
              break;
            
            case NNULL:
              printf ("NNULL ");
              break;
            
            default:
              printf ("%d ", op);
              break;
            }
        }
    }
  printf ("\n");
}