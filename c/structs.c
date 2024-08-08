/*
 * struct - Offset of & Container of macros
 *
 * Refer
 *
 * https://stackoverflow.com/a/39805594
 * https://radek.io/posts/magical-container_of-macro/
 */

#include <stdio.h>

#define offsetof(st, m) ((size_t) & ((st *)0)->m)

#define container_of(ptr, type, member)                                      \
	({                                                                   \
		const typeof(((type *)0)->member) *__mptr = (ptr);           \
		(type *)((char *)__mptr - offsetof(type, member));           \
	})

// =======
// Example
// =======
struct my_struct {
	const char *name;
	struct list_node list;
};

struct list_node *list_next(struct list_node *);

void iterate_list()
{
	struct list_node *current; /* ... */

	while (current) {
		struct my_struct *element =
		    container_of(current, struct my_struct, list);
		printf("%s\n", element->name);
		current = list_next(&element->list);
	}
}

int main(int, char **)
{
	/* iterate_list() */
	return 0;
}
