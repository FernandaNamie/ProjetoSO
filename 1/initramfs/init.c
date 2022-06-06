#include <stdio.h>
#include "cfs.h"

int main()
{
   char virtualRuntime[200];
   size_t virtualRuntimeSize = 200;
   int aux = 0;
   char c;
   int x;

   while (1) { 
      // pidt_t pid = fork();

      // if (pid == -1) {
      //    perror("fork");
		// 	return -1;
      // } else if (pid) {
      //    if (pid % 2 == 0) {
      //       c = getc(stdin);
      //    } else {
      //       x = 2 + 5;
      //    }
      // }
      
      // if (aux % 5 == 0) {
      //    cfs(virtualRuntime, virtualRuntimeSize);
      // }

      // aux++;

      cfs(virtualRuntime, virtualRuntimeSize);
      printf("%s", virtualRuntime);
   }
   return 0;
}
