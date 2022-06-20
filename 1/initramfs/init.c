#include <stdio.h>
#include "cfs.h"

static const char * const programs[] = { "/simple_arithmetic", "/write_file" };

int main(){
   char virtualRuntime[300];
   size_t virtualRuntimeSize = 300;

   const int len = sizeof programs / sizeof programs[0];

   for (int i = 0; i < len; i++) {
      const char *path = programs[i];
      pid_t pid = fork();
      if(pid == -1){
         panic("fork");
      } else if (pid) {
         printf("Iniciando execução %s (PID = %d)\n", path, pid);
         cfs(virtualRuntime, virtualRuntimeSize);
      } else {
         execl(path, path, (char *)NULL);
         panic("execl");
      }
   }
   for(;;)
      cfs(virtualRuntime, virtualRuntimeSize);

   return 0;
}

