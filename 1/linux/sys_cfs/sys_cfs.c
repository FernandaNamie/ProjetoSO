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
    int i;
    for (i = 0; i < 20 ; i++) {
        pr_info("pid%03d: %llu; \n",
            scheduled_task_list[i]->pid, scheduled_task_list[i]->se.vruntime);
    }
	return pr_info("---\n");
}