typedef struct spinlock{
	int locked;
} spin_lock;

//spin_lock LOCK;

enum lock_status{UNLOCKED, LOCKED};

int athread_spinLock(spin_lock *lock);

int athread_spinUnlock(spin_lock *lock);
void athread_spinlockInit(spin_lock *lock);
