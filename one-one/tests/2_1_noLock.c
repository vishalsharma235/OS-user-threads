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

int c = 0, c1 = 0, c2 = 0, c3 = 0, run = 1;
spin_lock LOCK1;

void *trial1(void*arg){
        while(run == 1){
                // athread_spinLock(&LOCK1);
                c++;
                // athread_spinUnlock(&LOCK1);
                c1++;
        }
}

void *trial2 (void*arg){
        while(run == 1){
                // athread_spinLock(&LOCK1);
                c++;
                // athread_spinUnlock(&LOCK1);
                c2++;
        }
}

void *trial3 (void*arg){
        while(run == 1){
                // athread_spinLock(&LOCK1);
                c++;
                // athread_spinUnlock(&LOCK1);
                c3++;
        }
}

int main() {
        athread_init();

        athread_spinlockInit(&LOCK1);

        athread_t t1 = 10, t2 = 11, t3 = 20;

        athread_create(&t1, NULL, trial1, NULL);
        athread_create(&t2, NULL, trial2, NULL);
        athread_create(&t3, NULL, trial3, NULL);
        sleep(2);
        run = 0;
        athread_join(t1, NULL);
        athread_join(t2, NULL);
        athread_join(t3, NULL);

        printf("c = %d  c1 = %d  c2 = %d  c3 = %d  c1+c2+c3 = %d\n", c, c1, c2,c3, c1+c2+c3);

        if(c == c1+c2+c3) {
            printf("FAILED\n");
        }
        else {
            printf("PASSED\n");
        }

        return 0;
}


