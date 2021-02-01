#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *	push, pop, access_top
 */

typedef struct node {
	void *data;
	int size;
	struct node *next;
}node;

typedef struct stack {
	struct node *top;
}stack;

int push(stack *st, void *data, int size) {
	if (st->top == NULL) {
		st->top = malloc(sizeof(node));
		st->top->size = size;
		st->top->data = malloc(size);
		memcpy(st->top->data, data, size);
		st->top->next = NULL;
	}
	else {
		node *temp = malloc(sizeof(node));
		temp->size = size;
		temp->data = malloc(size);
		memcpy(temp->data, data, size);
		temp->next = st->top;
		st->top = temp;
	}
	return 0;
}

int pop(stack *st) {
	if (st->top == NULL) {
		return -1;
	}
	node *temp = st->top;
	st->top = st->top->next;
	free(temp->data);
	free(temp);
	return 0;
}

struct node *access_top(stack *st) {
	return st->top;
}

int main () {
	stack st;
	int a=10, b=20;
	push(&st, &a, sizeof(int));
	push(&st, &b, sizeof(int));
	push(&st, &a, sizeof(int));
	push(&st, &b, sizeof(int));
	pop(&st);
	pop(&st);
	pop(&st);
	pop(&st);
	printf("TOP:%d\n", *(int *)(access_top(&st)->data));
	return 0;
}
