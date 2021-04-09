#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#define FOREACH(i, max, x) \
	do { \
		for (i=0; i<max; i++) { \
			(x); \
		} \
	} \
	while(0);

#define FOREACH_2D(o, omax, i, imax, x) \
	do { \
		for (o=0; o<omax; o++) { \
			for (i=0; i<imax; i++)	{ \
				(x); \
			} \
		} \
	} \
	while(0);

#ifdef DEBUG
	#define PLL(x)		printf("%lld ", x)
	#define PI(x)		printf("%d ", x)
	#define PD(x)		printf("%lf ", x)
	#define PS(x)		printf("%s ", x)
	#define PC(x)		printf("%c ", x)
	#define P(fmt, x)	printf(fmt, x)
	#define PN()		printf("\n")
	#define PRINTER(i, max, x)	\
		do { \
			FOREACH(i, max, x); \
			PN(); \
		} \
		while(0);
	#define PRINTER_2D(o, omax, i, imax, x)	\
		do { \
			FOREACH_2D(o, omax, i, imax, x); \
			PN(); \
		} \
		while(0);
#else
	#define PLL(x)
	#define PD(x)
	#define PS(x)
	#define PC(x)
	#define P(x)
	#define PN()
	#define PRINTER(i, max, x)
#endif

/*
 * 	Print helper APIS
 */
void print_header(const char *s) {
	PS(s);
	PN();
}

void int_printer(int *arr, int num_els) {
	int i=0;
	PRINTER(i, num_els, PI(arr[i]));
}

void int2D_printer(int *arr, int num_els, int dim) {
	int i=0, j=0;
	PRINTER_2D(i, num_els, j, dim, PI(*(arr + i*dim + j)));
}

void ptr2D_printer(int **arr, int num_els, int dim) {
	int i=0, j=0;
	PRINTER_2D(i, num_els, j, dim, PI(arr[i][j]));
}

void ch_printer(char *arr, int num_els) {
	int i=0;
	PRINTER(i, num_els, PC(arr[i]));
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
	PRINTER(i, num_els, printf("%s %d %lf ", ptr[i]->name, ptr[i]->id, ptr[i]->rating));
}

/*
 * 	sort based on rating of the employees
 * 	also based on the lexographical string
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

int asc_str(const void *el1, const void *el2) {
	struct record *p1 = *(struct record **)el1;
	struct record *p2 = *(struct record **)el2;
	return strcmp(p1->name, p2->name);
}

int des_str(const void *el1, const void *el2) {
	struct record *p1 = *(struct record **)el1;
	struct record *p2 = *(struct record **)el2;
	return strcmp(p2->name, p1->name);
}
/*
 * 	Sort characters
 */
int asc_ch(const void *el1, const void *el2) {
	return *(char *)el1 - *(char *)el2;
}

int des_ch(const void *el1, const void *el2) {
	return *(char *)el2 - *(char *)el1;
}

/*
 * 	Sort strings
 */
int asc_pure_str(const void *el1, const void *el2) {
	char *s1 = *(char **)el1;
	char *s2 = *(char **)el2;
	return strcmp(s1, s2);
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
	qsort(st_p, 5, sizeof(struct record *), asc_str);
	st_printer(st_p, 5);

	print_header("/*	array of characters	*/");
	char ch_arr[5] = {'a', '9', '8', '7', '6'};
	ch_printer(ch_arr, 5);
	qsort(ch_arr, 5, sizeof(char), asc_ch);
	ch_printer(ch_arr, 5);

	print_header("/*	array of strings	*/");
	char **str_p = (char **)calloc(5, sizeof(char *));
	FOREACH(i, 5, 	str_p[i] = (char *)calloc(100, sizeof(char)));
	FOREACH(i, 5,	memcpy(str_p[i], names[i], sizeof(char *)));
	PRINTER(i, 5, PS(str_p[i]));
	qsort(str_p, 5, sizeof(char *), asc_pure_str);
	PRINTER(i, 5, PS(str_p[i]));
}
