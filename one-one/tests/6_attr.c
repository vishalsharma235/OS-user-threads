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

void *trial2(void*arg){
	printf("ATTR WORKING PROPERLY");
}

int main(){
    athread_init();
    athread_t t1 = 10;

    size_t sz = 10240;
    athread_attr_t *attr = (athread_attr_t*) malloc(sizeof(athread_attr_t));
    athread_attr_init(attr);
    void* sb = malloc(sizeof(sz));
    
    athread_attr_setstacksize(attr, sz);
    athread_attr_setstackaddr(attr, sb);

    athread_create(&t1, attr, trial2, NULL);

    athread_join(t1, NULL);

}