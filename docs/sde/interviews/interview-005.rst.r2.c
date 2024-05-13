/**
 * Linked list
 *
 * Input:
 *
 * 0    1    2    3
 * a -> b -> c -> d
 *
 * start = 1, end = 2
 *
 * Output:
 *
 * 0    1    2    3
 * a -> c -> b -> d
 */

typedef struct Node {
	struct Node *next;
	int data;
} List;

List *rev_list(List *head, int start, int end)
{
	List *curr = head, *prev = NULL, *next = NULL;
	int i = 0;

	while (i++ < start) {
		prev = curr;
		curr = curr->next;
	}

	List *h1 = NULL, t1 = curr;

	while (curr && i++ < end) {
		next = curr->next;
		curr->next = h1;
		h1 = curr;
		curr = next;
	}

	prev->next = h1;
	t1->next = curr;
	return curr;
}

/**
 * Inverse bits
 *
 * Input  : num = 101101, start = 1, end = 3
 * Output : num = 100011
 *
 * a = 110, b = ~a;
 */

int inv_bits(int a, int start, int end)
{
	int b = a;
	int mask = 0, i = start;
	while (i++ < end) mask = 1 << i;
	int t = a & mask;
	t = ~t;
	b |= t;
	return b;
}
