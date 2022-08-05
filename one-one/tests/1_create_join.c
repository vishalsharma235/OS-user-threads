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

int x, y, z;

void *func1(void *arg){
	x = 3;
}

void *func2(void *arg){
	y = 2;
}

void *func3(void *arg){
	z = 1;
}

int main() {
	athread_init();
	x = y = z = 0;

    athread_t t1 = 10, t2 = 11, t3 = 20;

	athread_create(&t1, NULL, func1, NULL);
	athread_create(&t2, NULL, func2, NULL);
	athread_create(&t3, NULL, func3, NULL);

	sleep(2);

	athread_join(t1, NULL);
	athread_join(t2, NULL);
	athread_join(t3, NULL);

	if(x == 3 && y == 2 && z == 1) {
		printf("\nPASSED\n");
	}

	else {
		printf("\nFAILED\n");
	}
	
	return 0;
}
