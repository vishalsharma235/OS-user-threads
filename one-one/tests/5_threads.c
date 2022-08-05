#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>
#include "../userthreads.h"
#include <signal.h>
#include "../stack.h"
#include "../queue.h"
#include <setjmp.h>
#include "../spinlock.h"
#include <linux/futex.h>

int num;
int threads[200];
spin_lock LOCK1;

void *func1(void *arg){
	athread_spinLock(&LOCK1);
    num++;
    athread_spinUnlock(&LOCK1);
}


int main() {
	athread_init();
	num = 0;
    int i;


    for(i = 0; i < 200; i++){
        athread_create(&threads[i], NULL, func1, NULL);
    }

    sleep(2);

    for(i = 0; i < 200; i++){
        athread_join(threads[i], NULL);
    }
	
	if(num == 200) {
		printf("\nPASSED\n");
	}

	else {
		printf("\nFAILED\n");
	}
	
	return 0;
}
