#include "stack.h"
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stddef.h>

size_t stackSize(void) {
	struct rlimit stackSize;
	getrlimit(RLIMIT_STACK, &stackSize);
	return (stackSize.rlim_cur);
}

size_t pageSize(void) {
	return sysconf(_SC_PAGESIZE);
}

void *stackAllocate(size_t stacksz) {
	size_t pgsz = pageSize();

	void *base = (void *)mmap(NULL, stacksz + pgsz, PROT_WRITE | PROT_READ, 
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);

	if(base == MAP_FAILED)
		return NULL;

	if(mprotect(base, pgsz, PROT_NONE) == -1){
		munmap(base, stacksz + pgsz);
		return NULL;
	}

	void *stackBase = base + pgsz;
	
	return stackBase;
}

int stackDeallocate(void *stackBase, size_t stacksz){
	size_t pgsz = pageSize();
	return munmap(stackBase - pgsz, stacksz + pgsz);
}
