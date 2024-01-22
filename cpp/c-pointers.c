/**
 * Pointer operators precedence
 */

#include <stdio.h>
#include <stdlib.h>

void print_a(int *a, int n)
{
	printf("a: ");
	for (int i = 0; i < n; i++) { printf("%d ", a[i]); }
}

int main(int argc, char *argv[])
{
	int *ptr = (int *)malloc(5 * sizeof(int));
	int *p = ptr;
	for (int i = 0; i < 5; i++) *(ptr + i) = i;
	print_a(p, 5);
	printf("\tp: %d\n", *ptr++); // ptr -> index: 0, value: 0, ptr++
	print_a(p, 5);
	printf("\tp: %d\n", (*ptr)++); // ptr -> index: 1, value: 1, val++
	print_a(p, 5);
	printf("\tp: %d\n", *ptr); // ptr -> index: 1, value: 2
	print_a(p, 5);
	printf("\tp: %d\n", *++ptr); // ptr -> index: 2, value: 2, ++ptr
	print_a(p, 5);
	printf("\tp: %d\n", ++*ptr); // ptr -> index: 2, value: 3, ++val
	print_a(p, 5); // indices: 3, 4 with values: 3, 4 are unmodified
	printf("\n");
	free(p);
	return 0;
}
