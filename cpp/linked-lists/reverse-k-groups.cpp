/**
 * Singly Linked List - Reverse in K groups
 * ========================================
 *
 * Refer:
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/
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
NodePtr reverseKGroup(NodePtr head, int k)
{
	if (!head || !head->next || k < 2) return head;
	NodePtr dummy = new_node(0);
	dummy->next = head;
	NodePtr rprev(dummy);
	for (;;) {
		int ck = 0;
		NodePtr t = rprev->next;
		while (t) {
			if (++ck == k) break;
			t = t->next;
		}
		if (ck < k) break;
		NodePtr rtail = rprev->next;
		NodePtr curr = rtail, prev = nullptr, next = nullptr;
		for (int i = 0; i < k; i++) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		rprev->next = prev;
		rtail->next = curr;
		rprev = rtail;
	}
	return dummy->next;
}
} // namespace SinglyLinkedList

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _rev_check(i, k, e)                                                  \
	{                                                                    \
		NodePtr t = copy(i);                                         \
		NodePtr a = reverseKGroup(t, k);                             \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _rev_desc_prefix "Reverse in K groups"

#define _REV_NAME(var) var
#define _REV_DESC(var) _rev_desc_prefix " - " _rev_##var##_desc

#define _REV_TEST(var)                                                       \
	TEST(_REV_NAME(var), _REV_DESC(var))                                 \
	{                                                                    \
		using namespace _REV_NAME(var);                              \
		NodePtr ip = copy(vi_t{1, 2, 3, 4, 5});                      \
		vi_t _k{2, 3, 2};                                            \
		vector<NodePtr> _e{                                          \
		    copy(vi_t{2, 1, 4, 3, 5}),                               \
		    copy(vi_t{3, 2, 1, 4, 5}),                               \
		    copy(vi_t{3, 2, 1, 4, 5}),                               \
		};                                                           \
		int n = size(_e), i = 0;                                     \
		for (; i < (n - 1); i++) _rev_check(ip, _k[i], _e[i]);       \
		/* check negative case */                                    \
		NodePtr t = copy(ip);                                        \
		NodePtr a = reverseKGroup(t, _k[i]);                         \
		CHECK_NE(_e[i], a);                                          \
		SHOW_OUTPUT(ip, a);                                          \
	}

_REV_TEST(SinglyLinkedList);

INIT_TEST_MAIN();
