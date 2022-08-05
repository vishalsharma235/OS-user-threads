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

int a, b;
athread_t t1 = 10, t2 = 11;

void *trial1(void*arg){
	athread_kill(t1, SIGKILL);
	a = 10;
}

void *trial2(void*arg){
	b = 200;
}


int main(){
    athread_init();
	a = 10; b = 20;

	athread_create(&t1, NULL, trial1, NULL);
	athread_create(&t2, NULL, trial2, NULL);
    sleep(1);
	athread_join(t1, NULL);
	athread_join(t2, NULL);

	if(a == 10 && b == 200) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
	} 
	
	return 0;
}