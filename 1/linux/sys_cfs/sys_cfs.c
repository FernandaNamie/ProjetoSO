#include<linux/linkage.h>
#include<linux/module.h>
#include<linux/sched/signal.h>

void switchPlace(struct task_struct* a[], struct task_struct* b[]) {
    struct task_struct* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct task_struct* scheduled_task_list[], int n, int i) {
    int largest = i;  
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && scheduled_task_list[left]->se.vruntime > scheduled_task_list[largest]->se.vruntime)
        largest = left;
    if (right < n && scheduled_task_list[right]->se.vruntime > scheduled_task_list[largest]->se.vruntime )
        largest = right;
    if (largest != i) {
        switchPlace(&scheduled_task_list[i], &scheduled_task_list[largest]);
        heapify(scheduled_task_list, n, largest);
    }
}
void heapSort(struct task_struct* scheduled_task_list[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(scheduled_task_list, n, i);

    for (i = n - 1; i >= 0; i--) {
        switchPlace(&scheduled_task_list[0], &scheduled_task_list[i]);
        heapify(scheduled_task_list, i, 0);
    }
}
  
asmlinkage long sys_cfs(char * virtualRuntime, size_t virtualRuntimeSize)
{
    struct task_struct* task_list;
    struct task_struct* p;
    struct task_struct* scheduled_task_list[20];
    char* ptr = virtualRuntime;
    int counter = 0;

    for_each_process_thread(task_list, p) {
        scheduled_task_list[counter] = p;
        counter++;

        if (counter > 20) {
            goto fim;
        }
    }
    
fim:
    heapSort(scheduled_task_list, 20);
	return pr_info("pid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu; \npid%03d: %llu;\n --- \n",
        scheduled_task_list[0]->pid, scheduled_task_list[0]->se.vruntime,
        scheduled_task_list[1]->pid, scheduled_task_list[1]->se.vruntime,
        scheduled_task_list[2]->pid, scheduled_task_list[2]->se.vruntime,
        scheduled_task_list[3]->pid, scheduled_task_list[3]->se.vruntime,
        scheduled_task_list[4]->pid, scheduled_task_list[4]->se.vruntime,
        scheduled_task_list[5]->pid, scheduled_task_list[5]->se.vruntime,
        scheduled_task_list[6]->pid, scheduled_task_list[6]->se.vruntime,
        scheduled_task_list[7]->pid, scheduled_task_list[7]->se.vruntime,
        scheduled_task_list[8]->pid, scheduled_task_list[8]->se.vruntime,
        scheduled_task_list[9]->pid, scheduled_task_list[9]->se.vruntime,
        scheduled_task_list[10]->pid, scheduled_task_list[10]->se.vruntime,
        scheduled_task_list[11]->pid, scheduled_task_list[11]->se.vruntime,
        scheduled_task_list[12]->pid, scheduled_task_list[12]->se.vruntime,
        scheduled_task_list[13]->pid, scheduled_task_list[13]->se.vruntime,
        scheduled_task_list[14]->pid, scheduled_task_list[14]->se.vruntime,
        scheduled_task_list[15]->pid, scheduled_task_list[15]->se.vruntime,
        scheduled_task_list[16]->pid, scheduled_task_list[16]->se.vruntime,
        scheduled_task_list[17]->pid, scheduled_task_list[17]->se.vruntime,
        scheduled_task_list[18]->pid, scheduled_task_list[18]->se.vruntime,
        scheduled_task_list[19]->pid, scheduled_task_list[19]->se.vruntime);
}