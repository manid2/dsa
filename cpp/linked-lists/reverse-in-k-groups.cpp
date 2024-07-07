/**
 * Reverse a linked list in k groups
 * =================================
 *
 * Leetcode: [25. Reverse Nodes in k-Group][lc25]
 *
 * [lc25]: https://leetcode.com/problems/reverse-nodes-in-k-group/
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 *
 * Solution
 * --------
 *
 * Reverse a linked list in k groups iterative.
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Reverse linked list iterative */
ListNode *reverse(ListNode *head)
{
	ListNode *curr = head, *prev = nullptr, *next = nullptr;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return curr;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
	if (!head || !head->next || k < 2) return head;
	ListNode dummy(0);
	ListNode *prev_head = &dummy;
	prev_head->next = head;
	for (;;) {
		int ck = 0;
		ListNode *t = prev_head->next;
		while (t) {
			if (++ck == k) break;
			t = t->next;
		}
		if (ck < k) break;
		ListNode *next_head = prev_head->next;
		ListNode *curr = next_head, *prev = nullptr, *next = nullptr;
		for (int i = 0; i < k; i++) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		prev_head->next = prev;
		next_head->next = curr;
		prev_head = next_head;
	}
	return dummy.next;
}

int main(int argc, char *argv[])
{
	return 0;
}
