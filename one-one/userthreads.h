#include <setjmp.h>

typedef pid_t athread_t;
typedef struct {
	athread_t tid;
	int running;
	pid_t pid;
	sigjmp_buf context;
	void *stackBase;
	int stackSize;
	void *futex;
	void *args;
	void *res;
	void *(*func) (void *);
}athread;

typedef struct node {
	athread *tcb;
	struct node *next;
}threadNode;

typedef struct {
	threadNode *head;
	threadNode *tail;
} queue;

typedef struct{
	size_t stackSize;
	void* stackBase;
} athread_attr_t;

void athread_init();
static int athread_begin(void* thread);
int athread_kill( athread_t thread, int sig);
int athread_create(athread_t * thread, athread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int athread_join(athread_t th, void **retval);
void athread_exit(void *retval);





//Thread Queue Functions

void init(queue *Q);
int isEmpty(queue *Q);
void enqueue(queue *Q, athread *tcb);
athread *dequeue(queue *Q);
void display(queue *Q);
athread *search(queue *Q, pid_t id);



int athread_attr_init(athread_attr_t * attr);
int athread_attr_destroy(athread_attr_t* attr);
int athread_attr_getstacksize(athread_attr_t* attr, size_t * sz);
int athread_attr_setstacksize(athread_attr_t* attr, size_t sz);
int athread_attr_getstackaddr(athread_attr_t* attr, void **sB);
int athread_attr_setstackaddr(athread_attr_t* attr, void *sB);

