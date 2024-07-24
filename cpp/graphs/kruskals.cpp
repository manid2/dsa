/**
 * Kruskal's - Minimum Spanning Tree
 * =================================
 *
 * Refer:
 *
 * https://cp-algorithms.com/graph/mst_kruskal.html
 * https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html
 * https://favtutor.com/blogs/kruskal-algorithm-cpp 
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */
// Edge is a pair of nodes with weight [u, v, w]
using Edge = array<int, 3>;

// Graph is a pair of V nodes & array of E edges
using Graph = pair<int, vector<Edge>>;

/* Function object to sort edges by weight in ascending order
 *
 * This is similar to std::less<Edge>() except it doesn't call
 * std::lexicographical_compare to avoid comparing sequentially instead
 * compare by weights of the edges.
 */
struct LessEdge {
	bool operator()(const Edge &l, const Edge &r) const
	{
		return l[2] < r[2];
	}
};

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual Graph minSpanTree(Graph g) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n log n + n^2)
 * SC : O(V) => O(n)
 */
class _01_kruskal_simple : public _00_test
{
public:
	_01_kruskal_simple()
	    : _00_test("Kruskal's minimum spanning tree - Simple")
	{
	}

	Graph minSpanTree(Graph g) override
	{
		const int n = g.first;
		Graph o(n, {});
		vector<int> p(n);
		iota(p.begin(), p.end(), 0);

		ranges::sort(g.second, LessEdge());

		/* int c = 0; */ // minimum cost
		for (const auto &[u, v, w] : g.second) {
			int pu = p[u];
			int pv = p[v];

			if (pu == pv) continue;

			/* c += w; */
			o.second.push_back({u, v, w});

			for (int i = 0; i < n; i++) {
				if (p[i] == pu) p[i] = pv;
			}
		}
		return o;
	}
};

/* TC : O(n log n + alpha(n)) => O(n log n)
 *      where alpha(n) is the inverse Ackermann function => near O(1)
 * SC : O(V) => O(n)
 */
struct DSU {
	vector<int> parent, rank;

	DSU(int n) : parent(n), rank(n) {}

	void make_set(int v)
	{
		parent[v] = v;
		rank[v] = 0;
	}

	int find_set(int v)
	{
		if (v == parent[v]) return v;
		return parent[v] = find_set(parent[v]);
	}

	void union_sets(int a, int b)
	{
		a = find_set(a);
		b = find_set(b);
		if (a != b) {
			if (rank[a] < rank[b]) swap(a, b);
			parent[b] = a;
			if (rank[a] == rank[b]) rank[a]++;
		}
	}
};

class _02_kruskal_dsu : public _00_test
{
public:
	_02_kruskal_dsu()
	    : _00_test("Kruskal's minimum spanning tree - Disjoint Set Union")
	{
	}

	Graph minSpanTree(Graph g) override
	{
		const int n = g.first;
		DSU d(n);
		Graph o(n, {});
		for (int i = 0; i < n; i++) d.make_set(i);

		ranges::sort(g.second, LessEdge());

		/* int c = 0; */ // minimum cost
		for (const auto &[u, v, w] : g.second) {
			if (d.find_set(u) == d.find_set(v)) continue;

			/* c += w; */
			o.second.push_back({u, v, w});
			d.union_sets(u, v);
		}
		return o;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
template <class T, size_t N>
ostream &operator<<(ostream &out, const array<T, N> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) out << (i++ ? ", " : "") << e;
	out << "}";
	return out;
}

template <class T>
ostream &operator<<(ostream &out, const vector<T> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) out << (i++ ? ", " : "") << e;
	out << "}";
	return out;
}

ostream &operator<<(ostream &out, const Graph &g)
{
	out << "Graph nodes = " << g.first << ", edges = " << g.second;
	return out;
}

void test_impl(const vector<Graph> &ip, const vector<Graph> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		Graph t = f->minSpanTree(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: " << ip[i] << "  output: " << t
			     << "\n";
	}
}

void _append_test_data_01(vector<Graph> &ip, vector<Graph> &op)
{
	Graph i(4, {});
	i.second.push_back({0, 1, 10});
	i.second.push_back({1, 3, 15});
	i.second.push_back({2, 3, 4});
	i.second.push_back({2, 0, 6});
	i.second.push_back({0, 3, 5});

	Graph o(i.first, {});
	o.second.push_back({2, 3, 4});
	o.second.push_back({0, 3, 5});
	o.second.push_back({0, 1, 10});

	ip.push_back(i);
	op.push_back(o);
}

void _append_test_data_02(vector<Graph> &ip, vector<Graph> &op)
{
	Graph i(4, {});
	i.second.push_back({0, 1, 10});
	i.second.push_back({0, 2, 21});
	i.second.push_back({1, 2, 18});
	i.second.push_back({1, 3, 22});
	i.second.push_back({2, 3, 13});

	Graph o(i.first, {});
	o.second.push_back({0, 1, 10});
	o.second.push_back({2, 3, 13});
	o.second.push_back({1, 2, 18});

	ip.push_back(i);
	op.push_back(o);
}

int main(int, char **)
{
	vector<Graph> ip;
	vector<Graph> op;

	_append_test_data_01(ip, op);
	_append_test_data_02(ip, op);

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_kruskal_simple>(),
	    make_shared<_02_kruskal_dsu>(),
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
