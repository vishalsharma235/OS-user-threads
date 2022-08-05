#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>
#include "userthreads.h"
#include <signal.h>
#include "stack.h"
#include "queue.h"
#include <setjmp.h>
#include "spinlock.h"
#include <linux/futex.h>

static size_t stacksize;
queue threadQ;
spin_lock(LOCK);


static int futexWait(void * addr, int tid){
	return syscall(SYS_futex, addr, FUTEX_WAIT, tid, NULL, NULL, 0);
}
void athread_init(){
	init(&threadQ);
	stacksize = stackSize();
	athread* firstThread = (athread*)calloc(1, sizeof(athread));
	firstThread->func = NULL;
       	firstThread->args = NULL;
	firstThread->res = NULL;
	firstThread->stackBase = NULL;
	firstThread->stackSize = 0;
	firstThread->tid = syscall(SYS_gettid);
	enqueue(&threadQ, firstThread);
}

static int athread_begin(void* thread){

	athread* t = (athread*) thread;
	if(!sigsetjmp(t->context, 0))
		t->res = t->func(t->args);
	t->running = 0;
	return 0;
}

int athread_kill( athread_t thread, int sig){
	if( sig == 0)
		return 0;
	pid_t tid = getpid();
	int errCode;
	if( (errCode = tgkill(tid, thread, sig)) == -1)
		return errno;
	if(sig == SIGKILL){
		athread_spinLock(&LOCK);
		dequeue(&threadQ);
		athread_spinUnlock(&LOCK);
	}
	return 0;
}

int athread_create(athread_t * thread, athread_attr_t *attr, void *(*start_routine)(void *), void *arg){
	athread *t = (athread *) malloc(sizeof(athread));
	if( t == NULL )
		return EAGAIN;
	t->running = 1;
	t->func = start_routine;
	t->args = arg;
	t->stackBase = (attr) ? attr->stackBase : NULL;
	t->stackSize = (attr) ? attr->stackSize : stacksize;

	if(!t->stackBase)
		t->stackBase = stackAllocate(t->stackSize);
	
	if(!t->stackBase){
			free(t);
			return ENOMEM;
	}
	athread_spinLock(&LOCK);

	t->tid = clone(athread_begin, t->stackBase + t->stackSize,  CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM | CLONE_THREAD | CLONE_PARENT_SETTID| CLONE_CHILD_CLEARTID , t, &t->futex, t, &t->futex);
	if( t->tid == -1){
		stackDeallocate(t->stackBase, t->stackSize);
		free(t);
		athread_spinUnlock(&LOCK);
		return errno;
	}

	enqueue(&threadQ, t);
	*thread = t->tid;
	athread_spinUnlock(&LOCK);
	return 0;
}

int athread_join(athread_t th, void **retval){
	athread_spinLock(&LOCK);
	int status;
	athread* t = search(&threadQ, th);
	if ( t == NULL ) {
		athread_spinUnlock(&LOCK);
		return errno;
	}	
	futexWait(&t->futex, t->tid);
	if(retval)
		*retval = t->res;
	athread_spinUnlock(&LOCK);
	return 0;
}

void athread_exit(void *retval){
	int tid = gettid();
	athread *t = search(&threadQ, tid);
	t->res = retval;
	siglongjmp(t->context, 1);
}

int athread_equal(athread_t t1, athread_t t2) {
    return t1 - t2;
}


 



