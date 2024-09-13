/**
 * Least Recently Used (LRU) Cache
 * ===============================
 *
 * Refer:
 *
 * https://leetcode.com/problems/lru-cache
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
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

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string to_string(const vector<string> &c, const vi2_t &d)
{
	int n = size(c), i = 0;
	string im = format("LRUCache({})", d[i++][0]);
	for (; i < n; i++) {
		im += format(", {}", c[i]);
		int k = d[i][0];
		if (c[i] == "put") {
			int v = d[i][1];
			im += format("({}, {})", k, v);
		} else if (c[i] == "get")
			im += format("({})", k);
	}
	return im;
}

#define _lru_check(c, d, e)                                                  \
	{                                                                    \
		int n = size(c), i = 0;                                      \
		LRUCache cch(d[i++][0]);                                     \
		vi_t a;                                                      \
		for (; i < n; i++) {                                         \
			int k = d[i][0];                                     \
			if (c[i] == "put") {                                 \
				int v = d[i][1];                             \
				cch.put(k, v);                               \
			} else if (c[i] == "get")                            \
				a.push_back(cch.get(k));                     \
		}                                                            \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(to_string(c, d), a);                             \
	}

TEST(LRUCache, "Least Recently Used (LRU) Cache")
{
	vector<string> _c = {"LRUCache", "put", "put", "get", "put",
	                     "get",      "put", "get", "get", "get"};
	vi2_t _d = {{2}, {1, 1}, {2, 2}, {1}, {3, 3},
	            {2}, {4, 4}, {1},    {3}, {4}};
	vi_t _e = {1, -1, -1, 3, 4};
	_lru_check(_c, _d, _e);
}

INIT_TEST_MAIN();
