/*
 * _offset_of & _container_of macros
 * =================================
 *
 * Access a container using its member.
 *
 * Refer:
 *
 * https://stackoverflow.com/a/39805594
 * https://radek.io/posts/magical-container_of-macro/
 * https://www.kernel.org/doc/Documentation/driver-model/design-patterns.txt
 */

#include "tests.h"

/* ===========================================================================
 * Macro implementations
 * ===========================================================================
 */
// also defined in stddef.h
// clang-format off
#define _offset_of(st, m) ((size_t) &((st *)0)->m)
// clang-format on

#define _container_of(ptr, type, member)                                     \
	({                                                                   \
		const typeof(((type *)0)->member) *__mptr = (ptr);           \
		(type *)((char *)__mptr - _offset_of(type, member));         \
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

void _list_append(struct list_head *head, struct list_head *node)
{
	struct list_head *last = head->prev;
	node->next = head;
	node->prev = last;
	last->next = node;
	head->prev = node;
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
	_list_append(&task_list, &task1.tasks);
	_list_append(&task_list, &task2.tasks);
	_list_append(&task_list, &task3.tasks);

	// Iterate over tasks
	int i = 0;
	struct list_head *curr = NULL;
	list_for_each(curr, &task_list)
	{
		struct task_struct *task =
		    _container_of(curr, struct task_struct, tasks);
		a[i++] = task->state;
	}
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _of_desc_prefix "_offset_of & _container_of macros"
#define _of_desc_suffix "Access a container using its member"
#define _of_desc        _of_desc_prefix " - " _of_desc_suffix

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
    {_of_desc, test_iterate_list},
};

INIT_TEST_MAIN();
