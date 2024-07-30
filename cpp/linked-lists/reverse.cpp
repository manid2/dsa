/**
 * Singly Linked List - Reverse
 * ============================
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/reverse-a-linked-list/
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

	virtual NodePtr reverse(NodePtr head) = 0;

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
	_01_iterative() : _00_test("Singly Linked List - reverse iterative")
	{
	}

	NodePtr reverse(NodePtr head) override
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

void test_impl(vector<NodePtr> &ip, vector<NodePtr> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		const string test = format("test-{}", i);
		NodePtr t = f->reverse(_cp(ip[i]));
		if (_ne(t, op[i])) {
			cerr << f->getName() << ": " << test << " failed!"
			     << " list expected " << _l2s(op[i])
			     << ", actual " << _l2s(t) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  " << test << ":  "
			     << "input: list = " << _l2s(ip[i])
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

void _append_test_data_01(vector<NodePtr> &ip, vector<NodePtr> &op)
{
	vector<int> t{1, 2, 3, 4, 5};
	NodePtr i = _v2l(t);

	ranges::reverse(t);
	NodePtr o = _v2l(t);

	ip.push_back(i);
	op.push_back(o);
}

void _append_test_data_02(vector<NodePtr> &ip, vector<NodePtr> &op)
{
	vector<int> t{0, 2, 4, 6, 8};
	NodePtr i = _v2l(t);

	ranges::reverse(t);
	NodePtr o = _v2l(t);

	ip.push_back(i);
	op.push_back(o);
}

int main(int, char **)
{
	vector<NodePtr> ip;
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
