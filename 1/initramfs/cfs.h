#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_cfs 404

long cfs(char * virtualRuntime, size_t virtualRuntimeSize)
{
	return syscall(__NR_cfs, virtualRuntime, virtualRuntimeSize);
}
