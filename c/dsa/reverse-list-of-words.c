/*
 * Reverse a list of words and reverse each word in the list
 *
 * Example:
 *   Input: ["cisco", "juniper", "arista"]
 *   Ouput : ["atsira" , "repinuj", "ocsic"]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rev_word(char *w)
{
	size_t j = strlen(w) - 1;
	size_t i = 0;
	for (; i < j; i++, j--) {
		char t = w[i];
		w[i] = w[j];
		w[j] = t;
	}
}

void rev_list(char a[][10], size_t n)
{
	char t[10];
	for (int i = 0, j = n - 1; i < j; i++, j--) {
		strncpy(t, a[i], 10);
		strncpy(a[i], a[j], 10);
		strncpy(a[j], t, 10);
	}
}

void rev_list_words(char a[][10], size_t n)
{
	rev_list(a, n);
	for (int i = 0; i < n; i++) { rev_word(a[i]); }
}

void print_a(char a[][10], size_t n)
{
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i) printf(", ");
		printf("%s", a[i]);
	}
	printf("}\n");
}

int main(int argc, char *argv[])
{
	char a[][10] = {"cisco", "juniper", "arista"};
	size_t n = sizeof(a) / sizeof(a[0]);

	printf("Input: ");
	print_a(a, n);
	rev_list_words(a, n);
	printf("Output: ");
	print_a(a, n);
	return 0;
}
