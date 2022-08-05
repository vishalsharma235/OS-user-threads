#include <stddef.h>

size_t pageSize(void);

size_t stackSize(void);

void * stackAllocate(size_t stacksz);

int stackDeallocate(void *stackBase, size_t stacksz);
