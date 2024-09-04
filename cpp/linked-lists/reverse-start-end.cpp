/**
 * Singly Linked List - Reverse from start to end
 * ==============================================
 *
 * Refer:
 *
 * https://leetcode.com/problems/reverse-linked-list-ii/
 */

#include "tests.h"
#include "linked-lists.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _rev_SinglyLinkedList_desc "Singly Linked List"

/* TC : O(n)
 * SC : O(1)
 */
namespace SinglyLinkedList
{
NodePtr reverseBetween(NodePtr head, int start, int end)
{
	if (!head || (start == end)) return head;
	NodePtr curr = head, prev = nullptr, next = nullptr;
	int i = 0;
	while (i++ < start - 1 && curr) {
		prev = curr;
		curr = curr->next;
	}
	NodePtr rprev = prev, rtail = curr;
	while (i++ <= end && curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	if (rprev)
		rprev->next = prev;
	else
		head = prev;
	if (rtail) rtail->next = curr;
	return head;
}
} // namespace SinglyLinkedList

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _rev_check(i, m, n, e)                                               \
	{                                                                    \
		NodePtr t = copy(i);                                         \
		NodePtr a = reverseBetween(t, m, n);                         \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _rev_desc_prefix "Reverse between"

#define _REV_NAME(var) var
#define _REV_DESC(var) _rev_desc_prefix " - " _rev_##var##_desc

#define _REV_TEST(var)                                                       \
	TEST(_REV_NAME(var), _REV_DESC(var))                                 \
	{                                                                    \
		using namespace _REV_NAME(var);                              \
		NodePtr ip = copy(vi_t{1, 2, 3, 4, 5});                      \
		vi_t _m{2, 2};                                               \
		vi_t _n{4, 2};                                               \
		vector<NodePtr> _e{                                          \
		    copy(vi_t{1, 4, 3, 2, 5}),                               \
		    copy(vi_t{1, 2, 3, 4, 5}),                               \
		};                                                           \
		int n = size(_e);                                            \
		for (int i = 0; i < n; i++)                                  \
			_rev_check(ip, _m[i], _n[i], _e[i]);                 \
	}

_REV_TEST(SinglyLinkedList);

INIT_TEST_MAIN();
