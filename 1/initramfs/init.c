#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "cfs.h"

#define len(_arr) ((int)((&_arr)[1] - _arr))

void panic(const char *msg) {

	fprintf(stderr, "%s: %s (errno = %d)\n", msg, strerror(errno), errno);
	exit(-1);

}

static const char * const programs[] = { "/simple_arithmetic", "/write_file" };

int main(){
   char virtualRuntime[300];
   size_t virtualRuntimeSize = 300;

   for (int i = 0; i < len(programs); i++) {
      const char *path = programs[i];
      pid_t pid = fork();
      if(pid == -1){
         panic("fork");
      } else if (pid) {
         printf("Iniciando execução %s (PID = %d)\n", path, pid);
         cfs(virtualRuntime, virtualRuntimeSize);
      } else {
         execl(path, path, (char *)NULL);
         break;
      }
   }
   for(;;)
      cfs(virtualRuntime, virtualRuntimeSize);

   return 0;
}

