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


//int c = 0, c1 = 0, c2 = 0, c3 = 0;
//queue threadQ;
int c = 0, c1 = 0, c2 = 0, c3 = 0, run = 1;
spin_lock LOCK1;
void *func2(void *arg){
        printf("CREATE FUNC2 THREAD WORKING PROPERLY\n");
}


void *func(void *arg){
        for(int i = 0; i < 15; i++){
                if(i == 8){
                        int tid = gettid();
                        athread_kill(tid, SIGKILL);
                //      athread_exit(NULL);
                }

                printf("CREATE THREAD WORKING PROPERLY\n");
        }
}

void *trial1(void*arg){
        while(run == 1){
                athread_spinLock(&LOCK1);
                c++;
                athread_spinUnlock(&LOCK1);
                c1++;
        }
}

void *trial2 (void*arg){
        while(run == 1){
                athread_spinLock(&LOCK1);
                c++;
                athread_spinUnlock(&LOCK1);
                c2++;
        }
}

void *trial3 (void*arg){
        while(run == 1){
                athread_spinLock(&LOCK1);
                c++;
                athread_spinUnlock(&LOCK1);
                c3++;
        }
}

int main() {
        athread_init();
        athread_spinlockInit(&LOCK1);
        athread_t th = 10, th2 = 11, th3 = 20;
        athread_create(&th, NULL, func, NULL);
        athread_create(&th2, NULL, trial2, NULL);
        athread_create(&th3, NULL, trial3, NULL);
        sleep(2);
        run = 0;
        athread_join(th, NULL);
        athread_join(th2, NULL);
        athread_join(th3, NULL);
        printf("HELLO ANMOL");
        //athread_join(th3, NULL);
        printf("%d %d %d %d %d\n ", c, c1, c2,c3, c1+c2+c3);


        return 0;
}


