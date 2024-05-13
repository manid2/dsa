/**
 * linked lists common node
 *
 * Leetcode: 160. Intersection of Two Linked Lists
 *
 * Tags: #linked-lists, #two-pointers, #easy
 *
 * list a: 1 -> 2 -> 3 -> 4
 * list b: 6 -> 3 -> 4
 *
 * cmn_node: 2
 *
 *  a   b
 *  -----
 *  1   2
 *  2   4
 *  5
 *    3 // <- find
 *    4
 */

typedef struct Node {
	stuct Node next;
	int data;
} List;

/* Time complexity: O(n^2) square */
List *cmn_node(List *ah, List *bh)
{
	List *a = ah;
	List *b = bh;

	while (a) {
		while (b) {
			if (a->next == b->next) return a->next;
			b = b->next;
		}
		a = a->next;
	}
	return NULL;
}

/* Time compelxity: O(n) linear */
List *cmn_node(List *ah, List *bh)
{
	List *a = ah;
	List *b = bh;

	List *m[1024];

	int i = 0;
	while (a) {
		m[i++] = a;
		a = a->next;
	}

	i = 0;
	while (b) {
		if (m[i++] == b) return m[i];
		b = b->next;
	}
	return NULL;
}
