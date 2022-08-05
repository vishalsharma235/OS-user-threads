#include <stdio.h>
#include "spinlock.h"
#include <stdatomic.h>

int compareAndSwap(int *lockValue, int compareVal, int swapVal) {     
	return atomic_compare_exchange_strong(lockValue, &compareVal, swapVal);
}

void athread_spinlockInit(spin_lock *lock){
    lock->locked = UNLOCKED;
    return;
}

int athread_spinLock(spin_lock  *lock) {
    while (!compareAndSwap(&lock->locked, UNLOCKED, LOCKED)){
        continue;
    }
    return 0;
}

int athread_spinUnlock(spin_lock *lock) {
    compareAndSwap(&lock->locked, LOCKED, UNLOCKED);
    return 0;
}

