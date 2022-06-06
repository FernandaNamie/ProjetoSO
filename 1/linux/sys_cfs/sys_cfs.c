#include<linux/linkage.h>
#include<linux/module.h>
#include<linux/sched/signal.h>

asmlinkage long sys_cfs(char * virtualRuntime, size_t virtualRuntimeSize)
{
    struct task_struct* task_list;
    struct task_struct* p; 
    char* ptr = virtualRuntime;
    int counter = 0;

    for_each_process_thread(task_list, p) {
        ptr += sprintf(ptr, "%d", p->pid);
        ptr += sprintf(ptr, ":");
        ptr += sprintf(ptr, "%d", p->se.vruntime);
        ptr += sprintf(ptr, " ");
        counter++;

        if (counter > 20) {
            goto fim;
        }
    }
    
fim:
	return 1;
}