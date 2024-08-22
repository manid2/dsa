/**
 * Rearrange linked list in-place
 * ==============================
 *
 * Alternating Split and Merge of a Linked List.
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/rearrange-a-given-linked-list-in-place/
 * https://leetcode.com/problems/reorder-list/
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

NodePtr _middle(NodePtr head)
{
	NodePtr fast = head, slow = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

NodePtr _reverse(NodePtr head)
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

NodePtr _merge_alt(NodePtr l1, NodePtr l2)
{
	NodePtr ah = l1, t = nullptr;
	while (l1 && l2) {
		t = l1->next;
		l1->next = l2;
		l1 = t;

		t = l2->next;
		l2->next = l1;
		l2 = t;
	}
	return ah;
}

NodePtr rearrange(NodePtr head)
{
	if (!head || !head->next) { return head; }
	NodePtr m = _middle(head);
	NodePtr l2 = m->next;
	m->next = NULL;
	l2 = _reverse(l2);
	return _merge_alt(head, l2);
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(rearrange, "Singly Linked List - Rearrange alternate split & merge.")
{
	NodePtr i, e, t, a;
	i = copy(vi_t({'a', 'b', 'c', 'd', 'e', 'f', 'g'}));
	e = copy(vi_t({'a', 'g', 'b', 'f', 'c', 'e', 'd'}));
	t = copy(i);
	a = rearrange(t);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

INIT_TEST_MAIN();
