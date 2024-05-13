// calsoft round 2

struct A {
	int a;
	int b;
	int c;
}

static inline size_t
get_offset_of(int mem)
{
	return ((struct A *)-((struct A *)->mem));
}

// custom malloc to return 128 byte aligned pointer to memory

static const int sys_mem_align = 128;
static const int sys_mem_buf[10000 * sys_mem_align];

typedef struct memblock {
	size_t size;
	bool is_free;
	void *ptr;
} MemBlocks;

void *my_malloc(size_t size)
{
	if (!size) return NULL;

	MemBlocks 8blocks [1000];
	MemBlocks 16blocks [1000];

	for (int i = 0; i < 1000; i++) {
		if (blocks[i].is_free) {
			blocks.size = size;
			// allocate a block from memory
			void *tmp = sys_mem_buf + i * size;
			// align the block to system memory alignment requirements
			size_t pdiff = tmp / sys_mem_align;
			if (!pdiff)
				blocks.ptr = tmp;
			else
				blocks.ptr = tmp + pdiff;
			blocks[i].is_free = FALSE;
			return blocks.ptr;
		}
	}
	return NULL;
}

/*
z = 0x1122 3344 5566 7788
x = 0x7788 5566 3344 1122
*/

void swap(uchar16_t *p1, uchar16_t *p2)
{
	uchar16_t t = *p1;
	*p1 = *p2;
	*p2 = t;
}

size_t swap_2b(size_t z)
{
	int end = sizeof(z);
	int begin = 0;
	while (begin < end) {
		swap(&z + begin, &z + end);
		begin += 2;
		end -= 2;
	}
	return z;
}

void swap(uchar8_t *p1, uchar8_t *p2)
{
	uchar8_t t = *p1;
	*p1 = *p2;
	*p2 = t;
}

size_t swap_2b(size_t z)
{
	char *begin = &z;
	char *end = begin + sizeof(z);
	while (begin < end) {
		for (int i = 0; i < 2; i++)
			swap((begin + i + 1, end - i - 1);
		begin += 2;
		end -= 2;
	}
	return z;
}

size_t *ptr = 16;
ptr = ptr + 4;
// ptr + (4 * sizeof(size_t))
