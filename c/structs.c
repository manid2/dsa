/*
 * struct - Offset of & Container of macros
 *
 * Refer
 *
 * https://stackoverflow.com/a/39805594
 * https://radek.io/posts/magical-container_of-macro/
 * https://www.kernel.org/doc/Documentation/driver-model/design-patterns.txt
 */

#include <stdio.h>
#include <stdlib.h>

/* ===========================================================================
 * Macro implementations
 * ===========================================================================
 */
// also defined in stddef.h
// clang-format off
#define offsetof(st, m) ((size_t) &((st *)0)->m)
// clang-format on

#define container_of(ptr, type, member)                                      \
	({                                                                   \
		const typeof(((type *)0)->member) *__mptr = (ptr);           \
		(type *)((char *)__mptr - offsetof(type, member));           \
	})

/* ===========================================================================
 * Example code
 * ===========================================================================
 */
// As used in include/linux/sched.h
struct list_head {
	struct list_head *next, *prev;
};

struct task_struct {
	int state;
	struct list_head tasks; // Must be a non-pointer for container_of()
	int flags;
};

static inline void list_add_tail(struct list_head *new,
                                 struct list_head *head)
{
	struct list_head *last = head->prev;
	new->next = head;
	new->prev = last;
	last->next = new;
	head->prev = new;
}

#define list_for_each(pos, head)                                             \
	for (pos = (head)->next; pos != (head); pos = pos->next)

void get_task_states(int *a)
{
	struct task_struct task1, task2, task3;
	struct list_head task_list;

	// Initialize list head
	task_list.next = &task_list;
	task_list.prev = &task_list;

	// Initialize tasks
	task1.state = 1;
	task2.state = 2;
	task3.state = 3;

	// Add tasks to list
	list_add_tail(&task1.tasks, &task_list);
	list_add_tail(&task2.tasks, &task_list);
	list_add_tail(&task3.tasks, &task_list);

	// Iterate over tasks
	int i = 0;
	struct list_head *curr = NULL;
	list_for_each(curr, &task_list)
	{
		struct task_struct *task =
		    container_of(curr, struct task_struct, tasks);
		a[i++] = task->state;
	}
}

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
#define array_size(a) (sizeof(a) / sizeof(a[0]))

#define fii(n) for (int i = 0; i < (n); i++)

static int check_eq_n(int *l, int *r, int n)
{
	fii (n) {
		if (l[i] != r[i]) return 0;
	}
	return 1;
}

static void _a2s(int *a, int n, char *b)
{
	int l = 0, f = 1;
	b[l++] = '{';
	fii (n) {
		l += sprintf(&b[l], "%s%d", (f ? "" : ", "), a[i]);
		f = 0;
	}
	b[l++] = '}';
	b[l] = '\0';
}

#define CHECK_EQ_N(l, r, n)                                                  \
	{                                                                    \
		char ab[100], eb[100];                                       \
		_a2s(l, n, ab);                                              \
		_a2s(r, n, eb);                                              \
		if (!check_eq_n(l, r, n)) {                                  \
			fprintf(stderr,                                      \
			        "  test-%d failed! "                         \
			        "expected %s, actual %s.\n",                 \
			        tc, ab, eb);                                 \
			exit(1);                                             \
		} else {                                                     \
			if (getenv("SHOW_TEST_OUTPUT"))                      \
				fprintf(                                     \
				    stdout,                                  \
				    "  test-%d:  input: %s,  output: %s.\n", \
				    tc, ab, eb);                             \
		}                                                            \
	}

#define RUN_ALL_TESTS()                                                      \
	size_t tc = 0, ts = 0;                                               \
	for (; ts < array_size(_tests); ts++) {                              \
		if (getenv("SHOW_TEST_OUTPUT"))                              \
			fprintf(stdout, "Testing implementation %d %s\n",    \
			        ts + 1, _tests[ts].desc);                    \
		tc += _tests[ts].func();                                     \
	}                                                                    \
	fprintf(stdout, "Executed %d implementations with %d tests.", ts, tc);

typedef int (*TestFuncPtr)();

struct TestsStruct {
	const char *desc;
	TestFuncPtr func;
};

#define TEST_LIST static struct TestsStruct _tests[]

/* ===========================================================================
 * Test code
 * ===========================================================================
 */

int test_iterate_list()
{
	int tc = 0;
	int a[5] = {0}, e[5] = {1, 2, 3};
	get_task_states(a);

	tc++;
	CHECK_EQ_N(e, a, 3);
	return tc;
}

TEST_LIST = {
    {"container_of: Access a container using its member", test_iterate_list},
};

int main(int, char **)
{
	RUN_ALL_TESTS();
	return 0;
}
