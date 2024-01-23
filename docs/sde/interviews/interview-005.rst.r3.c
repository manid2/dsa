/**
 * sorted array, remove repeated numbers
 *
 * Input:  [1 2 2 3 3 3 4 4 4 4 5 5 5 5 5]
 * Output: [1 2 3 4 5 0 0 0 0 0 0 0 0 0 0]
 *
 * Input:  [1 2 2 3 3] N=5, [6, 2+5+5, 3+5+5, 0, 0]
 * Output: [1 2 3 0 0] N=5, [6-5, 2+5+5-5, 3+5+5, 0, 0]
 */

void remove_repeated(int a[]. int size)
{
	// x ^ 0 = x
	// x ^ x = 0

	for (int i = 0; i < size; i++) {
		int id = a[i] % size;
		a[id] += size;
	}

	for (int i=0; i<size; i++) {
		while (a[i] / size >= 2 ) a[i] -= size;
	}
}

int clear_bit(int a, int pos)
{
	return (a & ~(1 << pos));
}

int get_bit_count(int a)
{
	// 1101
	int count = 0;
	while (a) {
		if (a & 1) count ++;
		a = a >> 1;
	}
	return count;
}

typedef struct Node {
	int d1, d2;
	char c1, ch2;
} List;

sizeof (List);

#define get_st_mem_offset (st, mem) (&(st *)->mem)
