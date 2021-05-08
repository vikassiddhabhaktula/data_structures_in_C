#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sll {
	void *data;
	int sz;
	void (*printer_fn)(void *, int);
	struct sll *next;
};

void print_ch(void *data, int sz) {
	char *ch_data = data;
	int i=0;
	for (i=0; i<sz; i++)	{
		printf("%c", ch_data[i]);
	}
}

struct sll *head = NULL;

/*
 * 	Function to add data at the head of the list, head also gets modified here.
 * 	args:
 * 		-	generic void * for data
 * 		-	size of the data
 * 		-	printer function which knows how to print this data
 */
int insert_at_head(struct sll **head, void *data, int sz, void (*printer_fn)(void *, int)) {
	struct sll *new = calloc(1, sizeof(struct sll));
	if (new == NULL)	return -1;
	new->data = calloc(1, sz);
	if (new->data == NULL)	return -2;
	new->sz = sz;
	memcpy(new->data, data, sz);
	new->printer_fn = printer_fn;
	if (*head == NULL) {
		new->next = NULL;
	}
	else {
		new->next = *head;
	}
	*head = new;
	return 0;
}

/*
 * 	Function to add data at the end of the list
 * 	args:
 * 		-	generic void * for data
 * 		-	size of the data
 * 		-	printer function which knows how to print this data
 */
int insert_at_end(struct sll **head, void *data, int sz, void (*printer_fn)(void *, int)) {
	if (*head == NULL) {
		return insert_at_head(head, data, sz, printer_fn);
	}
	struct sll *node = *head;
	while (node != NULL) {
		if (node->next != NULL) {
			node = node->next;
			continue;
		}
		break;
	}
	struct sll *new = calloc(1, sizeof(struct sll));
	if (new == NULL)	return -3;
	new->data = calloc(1, sz);
	if (new->data == NULL)	return -4;
	new->sz = sz;
	memcpy(new->data, data, sz);
	new->printer_fn = printer_fn;
	new->next = NULL;
	node->next = new;
	return 0;
}

/*
 * 	An example hook to add any functionality while walking the list
 * 	Feel free to extend it or add more return codes while walking.
 */
int capture_stuff(struct sll *node, void *data, int sz) {
	void *addr = &node;
	if (data == NULL)	return -1;
	memcpy(data, addr, sizeof(void *));
	return 0;
}

/*
 * 	function walks through the singly ll to print the values
 * 	and also do some other stuff for each node based on the function pointer passed in.
 * 	args:
 * 		-	head pointer of the singly ll
 * 		-	an array of pointers (or it could be anything) to be used
 * 		-	size of each element to be used from data
 * 		-	function pointer to act on the passed in data.
 */
void walk_the_list(struct sll *head, void **data, int sz, int (*capture_stuff)(struct sll *, void *, int sz)) {
	struct sll *node = head;
	int count = 0;
	while (node != NULL) {
		node->printer_fn(node->data, node->sz);
		if (capture_stuff != NULL && (data != NULL)) {
			if (capture_stuff(node, &(data[count]), sz))	printf ("ERR: passed in pointer is NULL\n");
			count++;
		}
		node = node->next;
	}
}

/*
 * 	function takes in array of sll node addresses and then works on that
 */
int is_sll_palindrome(void **addr, int num_els) {
	int head_idx = 0, tail_idx = num_els - 1;
	struct sll *head, *tail;
	while (head_idx < tail_idx) {
		head = (struct sll *)addr[head_idx++];
		tail = (struct sll *)addr[tail_idx--];
		if (memcmp(head->data, tail->data, head->sz)) return 0;
	}
	return 1;
}

/*
 * 	=======================================================================================
 * 	Pending functions:
 * 	lib:
 * 		-	Search for an element in the list
 * 		-	Remove a node from the list
 * 		-	Add after a node in the list
 * 	apis:
 * 		-	Check if the list is a palindrome by reversing half list
 * 			from middle.
 * 		-	Reverse the list
 * 		-	Build a stack using sll
 * 	=======================================================================================
 */

/*
 * 	Driver code
 * 		-	a passed in string characters get added as nodes in the sll.
 */
int main(int argc, char **argv) {
	char *str = argv[1];
	int len = strlen(str);
	int i=0;
	char ch;
	for (i=0; i<len; i++) {
		insert_at_end(&head, &str[i], sizeof(char), print_ch);
	}

	/*
	 * 	Create a list of pointers to store the address of the linked list
	 * 	for O(1) access like an array. But yes, it consumes space.
	 */
	void **addr = calloc(len, sizeof(void *));
	for (i=0; i<len; i++) {
		addr[i] = calloc(1, sizeof(void *));
	}
	walk_the_list(head, addr, sizeof(void *), capture_stuff); 
	printf(" %s\n", is_sll_palindrome(addr, len) ? "Palindrome" : "Not a palindrome");
	return 0;
}
