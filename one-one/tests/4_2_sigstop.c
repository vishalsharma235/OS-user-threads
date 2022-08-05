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

int a;
athread_t t1 = 10;

void *trial1(void*arg) {
	athread_kill(t1, SIGSTOP);
	a += 10;
}

int main(){
    athread_init();
	a = 0;

	athread_create(&t1, NULL, trial1, NULL);
    sleep(2);
	athread_join(t1, NULL);

	return 0;
}