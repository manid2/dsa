/**
 * Pointer operators precedence
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int *ptr = (int *)malloc(5 * sizeof(int));
	int *p = ptr;

	for (int i = 0; i < 5; i++) *(ptr + i) = i;

	printf("%d ", *ptr++);
	printf("%d ", (*ptr)++);
	printf("%d ", *ptr);
	printf("%d ", *++ptr);
	printf("%d ", ++*ptr);

	free(p);
	return 0;
}
