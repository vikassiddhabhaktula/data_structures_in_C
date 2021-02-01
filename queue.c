#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  enq, dq
 */

typedef struct node {
    void *data;
    int size;
    struct node *next;
    struct node *prev;
}node;

typedef struct queue {
    node *head;
    node *tail;
}queue;

int enq(queue *q, void *data, int size) {
    if (NULL == q->tail) {
        q->head = malloc(sizeof(node));
        q->head->data = malloc(size);
        q->head->size = size;
        memcpy(q->head->data, data, size);
        q->head->next = NULL;
        q->head->prev = NULL;
        q->tail = q->head;
    }
    else {
        node *temp = malloc(sizeof(node));
        temp->data = malloc(size);
        temp->size = size;
        temp->next = q->tail;
        q->tail->prev = temp;
        memcpy(temp->data, data, size);
        q->tail = temp;
    }
    return 0;
}

int dq(queue *q, void *data) {
    if (NULL == q->head) {
        return -1;
    }
    else {
        memcpy(data, q->head->data, q->head->size);
        node *temp = q->head;
        q->head = q->head->prev;
        free(temp->data);
        free(temp);
    }
    return 0;
}

int main() {
    int a=10, b=20, c=30;
    queue q;
    enq(&q, &a, sizeof(int));
    enq(&q, &b, sizeof(int));
    enq(&q, &c, sizeof(int));
    dq(&q, &a);
    dq(&q, &a);
    //dq(&q, &a);
    printf("HEAD:%d\nTAIL:%d\n", *(int *)q.head->data, *(int *)q.tail->data);
    return 0;
}

