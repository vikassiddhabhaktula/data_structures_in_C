#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*	insert, delete, search
*/

typedef struct node {
	void *data;
	int size;
	struct node *next;
	struct node *prev;
}node;

typedef struct bst {
	struct node *root;
}bst;

int ins(node **root, void *data, int size) {
	int cmp = 0;
	if (*root == NULL) {
		*root = malloc(sizeof(node));
		(*root)->data = malloc(size);
		(*root)->size = size;
		memcpy((*root)->data, data, size);
		(*root)->prev = NULL;
		(*root)->next = NULL;
	}
	else {
		cmp = memcmp(data, (*root)->data, size);
		if (cmp <= 0) {
			ins(&((*root)->prev), data, size);
		}
		else if (cmp > 0) {
			ins(&((*root)->next), data, size);
		}
	}
	return 0;
}

node *search (node *root, void *data, int size) {
	if (root == NULL)	return NULL;
	int cmp;
	cmp = memcmp(data, root->data, size);
	if (cmp == 0)	return root;
	else if (cmp < 0)	return search(root->prev, data, size);
	else	return search(root->next, data, size);	
}

void print_bst(node *root) {
	if (root == NULL) return;
	print_bst(root->prev);
	printf("%d\n", *(int *)root->data);
	print_bst(root->next);
}

int main () {
	int a=10, b=20, c=5;
	int d=7, e=19, f= 21;
	int x=100;
	bst tr;
	tr.root = NULL;
	ins(&(tr.root), &a, sizeof(int));
	ins(&(tr.root), &b, sizeof(int));
	ins(&(tr.root), &c, sizeof(int));
	ins(&(tr.root), &d, sizeof(int));
	ins(&(tr.root), &e, sizeof(int));
	ins(&(tr.root), &f, sizeof(int));
	print_bst(tr.root);
	printf("search:%d\n", search(tr.root, &x, sizeof(int)) == NULL ? 0 : 1);

	bst tch;	tch.root = NULL;
	char a1='c', b1= 'a', c1 = 't';
	ins(&(tch.root), &a1, sizeof(char));
	ins(&(tch.root), &b1, sizeof(char));
	ins(&(tch.root), &c1, sizeof(char));
	print_bst(tch.root);

	bst tf; tf.root = NULL;
	double ad=3.14, bd=4.5, cd=5.6;	
	ins(&(tf.root), &ad, sizeof(double));
	ins(&(tf.root), &bd, sizeof(double));
	ins(&(tf.root), &bd, sizeof(double));
	print_bst(tf.root);
	return 0;
}
