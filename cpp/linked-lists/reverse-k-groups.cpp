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

using namespace SinglyLinkedList;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
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

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(reverseKGroup, "Singly Linked List - reverse in K groups iterative")
{
	int k;
	NodePtr i, e, t, a;

	k = 2;
	i = copy(vi_t{1, 2, 3, 4, 5});
	e = copy(vi_t{2, 1, 4, 3, 5});
	t = copy(i);
	a = reverseKGroup(t, k);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);

	k = 3;
	i = copy(vi_t{1, 2, 3, 4, 5});
	e = copy(vi_t{3, 2, 1, 4, 5});
	t = copy(i);
	a = reverseKGroup(t, k);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);

	k = 2;
	i = copy(vi_t{1, 2, 3, 4, 5});
	e = copy(vi_t{3, 2, 1, 4, 5});
	t = copy(i);
	a = reverseKGroup(t, k);

	CHECK_NE(e, a);
	SHOW_OUTPUT(i, a);
}

INIT_TEST_MAIN();
