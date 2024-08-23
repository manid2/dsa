/*
 * Linked lists
 * ============
 *
 * Data structures and helper functions
 */

#pragma once

namespace SinglyLinkedList
{
struct Node;
using NodePtr = shared_ptr<Node>;
inline NodePtr new_node(int data) { return make_shared<Node>(data); }

struct Node {
	int data = 0;
	NodePtr next = nullptr;

	Node(int data) : data(data), next(nullptr) {}
};

// Helper functions
void append(NodePtr &tail, int data)
{
	auto node = new_node(data);
	if (tail) tail->next = node;
	tail = node;
}

bool operator==(NodePtr l, NodePtr r)
{
	while (l && r) {
		if (l->data != r->data) return false;
		l = l->next, r = r->next;
	}
	return (!l && !r);
}

bool operator!=(NodePtr l, NodePtr r) { return !(l == r); }

NodePtr copy(NodePtr node)
{
	NodePtr head = nullptr, tail = nullptr;
	for (int i = 0; node; node = node->next) {
		append(tail, node->data);
		if (!i++) head = tail;
	}
	return head;
}

NodePtr copy(const vector<int> &v)
{
	const int n = static_cast<int>(v.size());
	NodePtr head = nullptr, tail = nullptr;
	for (int i = 0; i < n; i++) {
		append(tail, v[i]);
		if (!i) head = tail;
	}
	return head;
}

ostream &operator<<(ostream &out, NodePtr node)
{
	out << "{";
	for (int i = 0; node; node = node->next)
		out << (i++ ? ", " : "") << node->data;
	out << "}";
	return out;
}
} // namespace SinglyLinkedList
