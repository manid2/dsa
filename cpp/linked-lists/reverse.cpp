/**
 * Singly Linked List - Reverse
 * ============================
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/reverse-a-linked-list/
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
NodePtr reverse(NodePtr head)
{
	NodePtr curr = head, prev = nullptr, next = nullptr;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}
} // namespace SinglyLinkedList

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _rev_check(i, e)                                                     \
	{                                                                    \
		NodePtr t = copy(i);                                         \
		NodePtr a = reverse(t);                                      \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _rev_desc_prefix "Reverse"

#define _REV_NAME(var) var
#define _REV_DESC(var) _rev_desc_prefix " - " _rev_##var##_desc

#define _REV_TEST(var)                                                       \
	TEST(_REV_NAME(var), _REV_DESC(var))                                 \
	{                                                                    \
		using namespace _REV_NAME(var);                              \
		vi2_t _v{                                                    \
		    {1, 2, 3, 4, 5},                                         \
		    {1, 2},                                                  \
		    {},                                                      \
		};                                                           \
		int n = size(_v);                                            \
		fii (i, n) {                                                 \
			vi_t _r(rbegin(_v[i]), rend(_v[i]));                 \
			NodePtr _i, _e;                                      \
			_i = copy(_v[i]);                                    \
			_e = copy(_r);                                       \
			_rev_check(_i, _e);                                  \
		}                                                            \
	}

_REV_TEST(SinglyLinkedList);

INIT_TEST_MAIN();
