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

void *trial1(void* arg) {
	athread_exit(arg);
}

void *trial2(void* arg) {
	athread_exit(arg);
}

void *trial3(void* arg) {
	athread_exit(arg);
}

int main() {
    athread_init();

    void *a, *b, *c;
    int t1, t2, t3, x = 5, y = 10, z = 15;

	athread_create(&t1, NULL, trial1, (void*)&x);
	athread_create(&t2, NULL, trial2, (void*)&y);
	athread_create(&t3, NULL, trial3, (void*)&z);

	athread_join(t1, &a);
	athread_join(t2, &b);
	athread_join(t3, &c);

	if(*((int*)a) == 5 && *((int*)b) == 10 && *((int*)c) == 15) {
		printf("PASSED\n");
	}
	
	return 0;
}