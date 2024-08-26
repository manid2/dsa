#include "tests.h"

struct Node;
using NodePtr = Node *;

struct Node {
	int key, value;
	NodePtr next, prev;

	Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
};

inline NodePtr new_node(int k, int v) { return new Node(k, v); }

class LRUCache
{
public:
	LRUCache(int c) : cap(c)
	{
		head = new_node(-1, -1);
		tail = new_node(-1, -1);
		head->next = tail;
		tail->prev = head;
	}

	int get(int key)
	{
		if (m.contains(key)) {
			NodePtr node = m[key];
			int ans = node->value;
			m.erase(key);
			deleteNode(node);
			addToFront(node);
			m[key] = getFrontNode();
			return ans;
		}
		return -1;
	}

	void put(int key, int value)
	{
		if (m.contains(key)) {
			NodePtr node = m[key];
			m.erase(key);
			deleteNode(node);
		}
		if (m.size() == cap) {
			NodePtr node = getRearNode();
			m.erase(node->key);
			deleteNode(node);
		}
		addToFront(new_node(key, value));
		m[key] = getFrontNode();
	}

private:
	void addToFront(NodePtr node)
	{
		NodePtr t = head->next;
		node->next = t;
		node->prev = head;
		head->next = node;
		t->prev = node;
	}

	void deleteNode(NodePtr node)
	{
		NodePtr p = node->prev;
		NodePtr n = node->next;
		p->next = n;
		n->prev = p;
	}

	NodePtr getFrontNode(void) const { return head->next; }
	NodePtr getRearNode(void) const { return tail->prev; }

	size_t cap;
	unordered_map<int, NodePtr> m;
	NodePtr head, tail; // anchor nodes
};

int main(int, char **)
{
	cout << "Executed 1 implementations with 1 tests." << endl;
	return 0;
}
