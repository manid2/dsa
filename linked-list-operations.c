#include <stdio.h>

typedef struct node {
	int data;
	struct node *next;
} LList;

// delete nth node in linked list
LList  *delete_nth_node(LList *head, int nth_node)
{
	LList *prev = head;
	LList *curr = head;
	int n = 0;
	while (curr) {
		prev = curr;
		curr = curr->next;
		if (n++ == nth_node) {
			prev->next = curr->next;
			free (curr);
		}
	}
}

int main(int argc, char *argv[])
{
	return 0;
}
