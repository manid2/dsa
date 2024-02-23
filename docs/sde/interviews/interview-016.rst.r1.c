// Zscalar round 1
// Software Engineer ( C ,TCP/IP protocol stack)

/*

typedef struct st_name {
    int x;
    int y;
}st_name_t;

0x010101

1. declare a pointer to a pointer to this structure
2. initialize this variable
3. pass to the below function
4. write a function which takes pointer to a pointer to this structure and
count the numnber of bits set in y only if the most significant bit of x is set 
return the count else return 0
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st_name {
	int x;
	int y;
} st_name_t;

int add_numbers(int a, int b) { return a + b; }

// 101 x = 5
// 100 x - 1 = 4
// 011 ~(x - 1)

int count_bits(int n)
{
	int c = 0;
	while (n) {
		n &= n - 1;
		c++;
	}
	return c;
}

int count_bits_msb(st_name_t **pst)
{
	int px = (*pst)->x;
	int py = (*pst)->y;
	int msb_bit = px & ~(px - 1);
	if (msb_bit) return count_bits(py);
	return 0;
}

int main()
{
	st_name_t st = {.x = 0xFF, .y = 0xF0};
	st_name_t *p1 = &st;
	st_name_t **pst = &p1; // initialized

	int num1, num2;
	scanf("%d %d", &num1, &num2);
	int sum;

	sum = add_numbers(num1, num2);
	printf("The sum is %d", sum);

	return 0;
}

/*
Write a function which takes the root of a tree and returns the edge elements of each level.
Add all these elements in a linked list and return the head to this list

sample input:

            1
        /       \
    2               3
  /   \           /   \
4       5       6       7

sample output:
1 2 3 4 7

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st_node {
	int data;
	struct st_node *next;
} List;

List node;
List *list_head = &node;

List *new_node(int item)
{
	List *n = malloc(sizeof(List));
	n->data = item;
	n->next = NULL;
	return n;
}

void list_append(int item)
{
	List *t = list_head;
	while (t) { t = t->next; }
	t = new_node(item);
}

typedef struct st_btree {
	int data;
	struct st_btree *left, *right;
} BTree;

typedef struct st_queue {
	BTree *data;
	int size, capacity;
	int front, rear;
} Queue;

Queue q = {.capacity = 10, .front = -1, .rear = -1};

void enqueue(int item)
{
	if (q.front == -1) {
		q.front++;
		q.rear = q.front;
		q.data[q.rear] = item; // create BTree node and assign ptr
	}
	if (q.rear < q.size) q.data[q.rear++] = item;
}

void dequeue()
{
	if (q.front > q.rear) return; // queue empty
	if (q.front <= q.rear) q.data[q.front++] = 0;
}

/*
sample input:

            1              - level 1
        /       \
    2               3      - level 2
  /   \           /   \
4       5       6       7  - level 3

sample output:
1 2 3 4 7
*/

List *level_order_tree(BTree *root)
{
	enqueue(root);
	while (q.size) {
		if (q.size == 1 && level == 1) {
			list_append(q.data[q.front]);
		} else if (!(q.size % 2)) {
			list_append(q.data[q.front]);
			list_append(q.data[q.rear]);
		}
		enqueue(root->left);
		enqueue(root->right);
		dequeue();
	}
	return list_head;
}

int main()
{
	int num1, num2;
	scanf("%d %d", &num1, &num2);
	int sum;

	sum = add_numbers(num1, num2);
	printf("The sum is %d", sum);

	return 0;
}
