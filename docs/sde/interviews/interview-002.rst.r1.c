/**
 * Calsoft Hyderabad
 * =================
 *
 * Senior Software Engineer
 * DPDK: C & Python
 * Round 1
 * 2024-01-18T11:18:51+0530
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	char *p = "abc";
	p[0] = 'c';
	printf ("%c\n", *p);
	return 0;
}


typedef struct Node {
	int data;
	struct Node *next;
} List;


List* reverse_list (List *head)
{
	List *curr=head, *prev=NULL, *next=NULL;
	while (curr->next) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return curr;
}


char mem[1024];

typedef struct memblock {
	size_t size;
	bool is_free;
	void *ptr;
} MemBlocks

void* my_malloc (size_t size)
{
	if (!size)
		return NULL;

	MemBlocks blocks[10];

	for (int i=0; i<10; i++) {
		if (blocks[i].is_free) {
			blocks.size = size;
			// handle mem overflow
			blocks.ptr = mem + i * size;
			return blocks.ptr;
		}
	}
	return NULL;
}
