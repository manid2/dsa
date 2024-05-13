/**
 * 2D dynamic array
 */

char **alloc_2d(int rows, int cols)
{
	char **matrix = (void *)malloc(rows);
	memset(matrix, 0, rows);
	if (!matrix) return NULL;

	for (int i = 0; i < rows; i++) {
		matrix[i] = (void *)malloc(cols);
		if (!matrix[i]) goto freecols;
	}

freecols:
	for (int i = 0; i < rows; i++) free(matrix[i]);

	return matrix;
}

/**
 * Delete duplicate single linked list unsorted elements
 *
 * Input:  [1, 2, 2, 3]
 * output: [1, 2, 3]
 */

typedef struct Node {
	struct Node *next;
	int data;
} List;

typedef struct map {
	int k, v;
} hash_map;

void del_dups(List *head)
{
	hash_map m[];
	List *curr = head;

	int i = 0;
	List *prev = head;
	while (curr->next) {
		m[i].k = curr->data;
		m[i].v++;
		prev = curr;
		if (m[i].v > 1) {
			List *t = curr->next;
			free(curr);
			curr = t;
		}
		curr = curr->next;
	}
}
