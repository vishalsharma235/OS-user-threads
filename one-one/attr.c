#include<stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "userthreads.h"
#include "stack.h"


int athread_attr_init(athread_attr_t * attr){
	if(!attr)
		return EINVAL;
	attr->stackBase = NULL;
	attr->stackSize = stackSize();
	return 0;
}

int athread_attr_destroy(athread_attr_t* attr){
	if (!attr)
		return EINVAL;
	free(attr);
	return 0;
}

int athread_attr_getstacksize(athread_attr_t* attr, size_t * sz){
	if (!attr)
		return EINVAL;
	*sz =  (attr->stackSize);
	return 0;
}

int athread_attr_setstacksize(athread_attr_t* attr, size_t sz){
        if (!attr)
                return EINVAL;
        (attr->stackSize) = sz;
        return 0;
}


int athread_attr_getstackaddr(athread_attr_t* attr, void **sB){
	if (!attr)
		return EINVAL;
	*sB = attr->stackBase;
	return 0;
}

int athread_attr_setstackaddr(athread_attr_t* attr, void *sB){
	if (!attr)
		return EINVAL;
	attr->stackBase = sB;
	return 0;
}
