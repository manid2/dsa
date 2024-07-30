/**
 * Singly Linked List - Reverse in K groups
 * ========================================
 *
 * Refer:
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */

struct Node;
using NodePtr = shared_ptr<Node>;
inline NodePtr new_node(int data) { return make_shared<Node>(data); }

struct Node {
	int data = 0;
	NodePtr next = nullptr;

	Node(int data) : data(data), next(nullptr) {}
};

void list_append(NodePtr &tail, int data)
{
	auto node = new_node(data);
	if (tail) tail->next = node;
	tail = node;
}

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual NodePtr reverseKGroup(NodePtr head, int k) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
class _01_iterative : public _00_test
{
public:
	_01_iterative()
	    : _00_test("Singly Linked List - reverse in K groups iterative")
	{
	}

	NodePtr reverseKGroup(NodePtr head, int k) override
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
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string _l2s(NodePtr node)
{
	ostringstream out;
	out << "{";
	for (int i = 0; node; node = node->next) {
		out << (i++ ? ", " : "") << node->data;
	}
	out << "}";
	return out.str();
}

bool _eq(NodePtr l, NodePtr r)
{
	while (l && r) {
		if (l->data != r->data) return false;
		l = l->next, r = r->next;
	}
	return (!l && !r);
}

bool _ne(NodePtr l, NodePtr r) { return !_eq(l, r); }

NodePtr _cp(NodePtr node)
{
	NodePtr head = nullptr, tail = nullptr;
	for (int i = 0; node; node = node->next) {
		list_append(tail, node->data);
		if (!i++) head = tail;
	}
	return head;
}

using ip_t = pair<NodePtr, int>;

void test_impl(vector<ip_t> &ip, vector<NodePtr> &op, shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		const string test = format("test-{}", i);
		const auto &[n, k] = ip[i];
		NodePtr t = f->reverseKGroup(_cp(n), k);
		if (_ne(t, op[i])) {
			cerr << f->getName() << ": " << test << " failed!"
			     << " list expected " << _l2s(op[i])
			     << ", actual " << _l2s(t) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  " << test << ":  "
			     << "input: list = " << _l2s(n) << ", k = " << k
			     << "  output: list = " << _l2s(t) << "\n";
	}
}

NodePtr _v2l(const vector<int> v)
{
	const int n = static_cast<int>(v.size());
	NodePtr head = nullptr, tail = nullptr;
	for (int i = 0; i < n; i++) {
		list_append(tail, v[i]);
		if (!i) head = tail;
	}
	return head;
}

void _append_test_data_01(vector<ip_t> &ip, vector<NodePtr> &op)
{
	const int k = 2;
	vector<int> t{1, 2, 3, 4, 5};
	NodePtr i = _v2l(t);

	t = {2, 1, 4, 3, 5};
	NodePtr o = _v2l(t);

	ip.emplace_back(i, k);
	op.push_back(o);
}

void _append_test_data_02(vector<ip_t> &ip, vector<NodePtr> &op)
{
	const int k = 3;
	vector<int> t{1, 2, 3, 4, 5};
	NodePtr i = _v2l(t);

	t = {3, 2, 1, 4, 5};
	NodePtr o = _v2l(t);

	ip.emplace_back(i, k);
	op.push_back(o);
}

int main(int, char **)
{
	vector<ip_t> ip;
	vector<NodePtr> op;

	_append_test_data_01(ip, op);
	_append_test_data_02(ip, op);

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_iterative>(),
	};

	for (size_t i = 0; i < impls.size(); i++) {
		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "Testing implementation " << i + 1 << " "
			     << impls[i]->getName() << "\n";

		test_impl(ip, op, impls[i]);
	}

	cout << "Executed " << impls.size() << " implementations"
	     << " with " << ip.size() << " tests." << endl;
	return 0;
}
