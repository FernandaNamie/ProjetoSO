#include "cfs.h"

int main()
{
   char virtualRuntime[200];
   size_t virtualRuntimeSize = 200;

   while (1) { 
      cfs(virtualRuntime, virtualRuntimeSize);
      printf("%s", virtualRuntime);
   }
   return 0;
}
