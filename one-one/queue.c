#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "userthreads.h"

void init(queue *Q) {
        Q->head = NULL;
        Q->tail = NULL;
}

int isEmpty(queue *Q) {
        return Q->head == NULL;
}

void enqueue(queue *Q, athread *tcb) {
        threadNode *n = malloc(sizeof(threadNode));
        n->tcb = tcb;
        n->next = NULL;

        if(isEmpty(Q)) {
                Q->head = n;
                Q->tail = n;
        }
        else {
                Q->tail->next = n;
                Q->tail = n;
        }

        return;
}

athread *dequeue(queue *Q) {
        if(isEmpty(Q))
                return NULL;

        threadNode *n = Q->head;
        athread *mtd = Q->head->tcb;

        Q->head = Q->head->next;

        if(Q->head == NULL)
                Q->tail = NULL;

        free(n);
        return mtd;
}

void display(queue *Q) {
        if(isEmpty(Q))
                return;

        threadNode *ptr = Q->head;

        while(ptr){
                printf("%u ", ptr->tcb->tid);
                ptr = ptr->next;
        }
        printf("\n");
}

athread *search(queue *Q, pid_t id) {
        if(isEmpty(Q))
                return NULL;

        threadNode *ptr = Q->head;
        while(ptr){
                if(ptr->tcb->tid == id)
                        return ptr->tcb;
                ptr = ptr->next;
        }
        return NULL;
}



