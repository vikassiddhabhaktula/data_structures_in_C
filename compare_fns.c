#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 	Print helper APIS
 */
void print_header(const char *s) {
	printf("%s\n", s);
}

void int_printer(int *arr, int num_els) {
	int i=0;
	for (i=0; i<num_els; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void int2D_printer(int *arr, int num_els, int dim) {
	int i=0, j=0;
	for (i=0; i<num_els; i++) {
		for (j=0; j<dim; j++)
			printf("%d ", *(arr + i*dim + j));
		printf("\t");
	}
	printf("\n");
}

void ptr2D_printer(int **arr, int num_els, int dim) {
	int i=0, j=0;
	for (i=0; i<num_els; i++) {
		for (j=0; j<dim; j++)
			printf("%d ", arr[i][j]);
		printf("\t");
	}
	printf("\n");
}

/*	int compare	*/
int asc_int(const void *el1, const void *el2) {
	return *(int *)el1 - *(int *)el2;
}

int des_int(const void *el1, const void *el2) {
	return *(int *)el2 - *(int *)el1;
}

/*	2D int compare
 *	Compare first element of the 2D array
 *	and then sort based on its value the whole 2D array
 */
int asc_int2D(const void *el1, const void *el2) {
	int *p1 = (int *)el1;
	int *p2 = (int *)el2;
	return p1[0] - p2[0];
}

int des_int2D(const void *el1, const void *el2) {
	int *p1 = (int *)el1;
	int *p2 = (int *)el2;
	return p2[0] - p1[0];
}

/*
 * 	double pointer compare function
 * 	Need to compare the first element and then
 * 	swap the (int *) pointers accordingly
 */
int asc_ptr2D(const void *el1, const void *el2) {
	int *p1 = *(int **)el1;
	int *p2 = *(int **)el2;
	return p1[0] - p2[0];
}

int des_ptr2D(const void *el1, const void *el2) {
	int *p1 = *(int **)el1;
	int *p2 = *(int **)el2;
	return p2[0] - p1[0];
}

/*
 * 	Dealing with structures
 * 	Employee record struct
 */
struct record {
	char name[100];
	int id;
	double rating;
};

void st_printer(struct record **ptr, int num_els) {
	int i=0;
	for (i=0; i<num_els; i++) {
		printf("%s %d %lf ", ptr[i]->name, ptr[i]->id, ptr[i]->rating);
	}
	printf("\n");
}

/*
 * 	sort based on rating of the employees
 */
int asc_st(const void *el1, const void *el2) {
	struct record *p1 = *(struct record **)el1;
	struct record *p2 = *(struct record **)el2;
	return p1->rating - p2->rating;
}

int des_st(const void *el1, const void *el2) {
	struct record *p1 = *(struct record **)el1;
	struct record *p2 = *(struct record **)el2;
	return p2->rating - p1->rating;
}

int main() {
	print_header("/*	Arrays	*/");
	int arr[5] = {3, 4, 1, 2, 5};
	int_printer(arr, sizeof(arr)/sizeof(arr[0]));
	qsort(arr, 5, sizeof(int), asc_int);
	int_printer(arr, sizeof(arr)/sizeof(arr[0]));
	qsort(arr, 5, sizeof(int), des_int);
	int_printer(arr, sizeof(arr)/sizeof(arr[0]));

	print_header("/*	2D arrays	*/");
	int arr2D[5][2] = {{2, 5}, {3, 6}, {1, 7}, {29, 1}, {-20, 9}};
	int2D_printer((int *)arr2D, 5, 2);
	qsort(arr2D, 5, 2 * sizeof(int), asc_int2D);
	int2D_printer((int *)arr2D, 5, 2);
	qsort(arr2D, 5, 2 * sizeof(int), des_int2D);
	int2D_printer((int *)arr2D, 5, 2);

	print_header("/*	array of pointers	*/");
	int m=5, n=2, i=0, j=0;
	int **arr_p = (int **)malloc(m * sizeof(int *));
	for (i=0; i<m; i++) {
		arr_p[i] = (int *)malloc(n * sizeof(int));
		for (j=0; j<n; j++)	arr_p[i][j] = arr2D[i][j];
	}
	ptr2D_printer(arr_p, 5, 2);
	qsort(arr_p, 5, sizeof(int *), asc_ptr2D);
	ptr2D_printer(arr_p, 5, 2);
	qsort(arr_p, 5, sizeof(int *), des_ptr2D);
	ptr2D_printer(arr_p, 5, 2);

	print_header("/*	array of structures	*/");
	char names[5][100] = {"vikas", "sruthi", "madhu", "mom", "dad"};
	struct record **st_p = (struct record **)malloc(m * sizeof(struct record *));
	for (i=0; i<m; i++) {
		st_p[i] = (struct record *)malloc(sizeof(struct record));
		st_p[i]->id = 7 - i;
		st_p[i]->rating = 0.5 + i;
		memcpy(st_p[i]->name, names[i], strlen(names[i]));
	}
	st_printer(st_p, 5);
	qsort(st_p, 5, sizeof(struct record *), des_st);
	st_printer(st_p, 5);
	qsort(st_p, 5, sizeof(struct record *), asc_st);
	st_printer(st_p, 5);
}
