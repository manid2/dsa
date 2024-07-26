/**
 * Prim's - Minimum Spanning Tree
 * ==============================
 *
 * Refer:
 *
 * https://cp-algorithms.com/graph/mst_prim.html
 * https://www.programiz.com/dsa/prim-algorithm
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */
const int X = INT_MAX;

// Edge is a pair of weight & to node
struct Edge {
	int w = X, v = -1;

	bool operator<(const Edge &r) const
	{
		return make_pair(w, v) < make_pair(r.w, r.v);
	}
};

// Graph is a V * V matrix where V is number of nodes
using Graph = vector<vector<int>>;

// Graph is adjacency list
using GraphAL = vector<vector<Edge>>;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual Graph minSpanTree(const Graph &g) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n^3)
 * SC : O(V) => O(n)
 */
class _01_prims_simple : public _00_test
{
public:
	_01_prims_simple() : _00_test("Prim's minimum spanning tree - simple")
	{
	}

	Graph minSpanTree(const Graph &g) override
	{
		const int n = static_cast<int>(g.size());
		Graph o(n, vector<int>(n, X));
		vector<bool> s(n, false); // selected nodes

		int u, v, w, e = 0 /* c = 0 // min cost */;
		while (e++ < n) {
			u = v = 0, w = X;
			for (int i = 0; i < n; i++) {
				if (!s[i]) continue;
				for (int j = 0; j < n; j++) {
					const int gw = g[i][j];
					if (s[j] || gw == X || w < gw)
						continue;
					u = i, v = j, w = gw;
				}
			}

			s[v] = true;
			/* c += w; */
			o[u][v] = w;

			// skip this for directed graph
			o[v][u] = w;
		}
		return o;
	}
};

/* TC : O(n^2)
 * SC : O(V) => O(n)
 */
class _02_prims_dg : public _00_test
{
public:
	_02_prims_dg()
	    : _00_test("Prim's minimum spanning tree - dense graphs")
	{
	}

	Graph minSpanTree(const Graph &g) override
	{
		const int n = static_cast<int>(g.size());
		Graph o(n, vector<int>(n, X));
		vector<bool> s(n, false); // selected nodes

		/* minimum weight edge to a selected node for each not yet
		 * selected node */
		vector<Edge> m(n);
		m[0].w = 0;

		/* int c = 0; */ // minimum cost
		for (int i = 0; i < n; i++) {
			int u = -1;
			for (int j = 0; j < n; j++) {
				if (!s[j] && (u == -1 || m[j].w < m[u].w))
					u = j;
			}

			if (m[u].w == X) {
				o = {}; // There is no edge so no MST
				break;
			}

			s[u] = true;
			/* c += m[u].w; */
			if (m[u].v != -1) {
				const int v = m[u].v;
				const int w = m[u].w;
				o[u][v] = w;

				// skip this for directed graph
				o[v][u] = w;
			}

			for (int v = 0; v < n; v++) {
				const int w = g[u][v];
				if (w < m[v].w) m[v] = {w, u};
			}
		}
		return o;
	}
};

/* TC : O(n log n)
 * SC : O(V) => O(n)
 */
class _02_prims_sg : public _00_test
{
public:
	_02_prims_sg()
	    : _00_test("Prim's minimum spanning tree - sparse graphs")
	{
	}

	Graph minSpanTree(const Graph &g) override
	{
		const int n = static_cast<int>(g.size());
		// convert to adjacency list
		GraphAL a(n);
		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++) {
				const int w = g[u][v];
				if (w != X) a[u].push_back({w, v});
			}
		return primsSparse(a);
	}

	Graph primsSparse(const GraphAL &g)
	{
		const int n = static_cast<int>(g.size());
		Graph o(n, vector<int>(n, X));
		vector<bool> s(n, false); // selected nodes

		/* minimum weight edge to a selected node for each not yet
		 * selected node */
		vector<Edge> m(n);
		m[0].w = 0;

		set<Edge> q;
		q.insert({0, 0});

		/* int c = 0; */ // minimum cost
		for (int i = 0; i < n; i++) {
			if (q.empty()) {
				o = {}; // There is no edge so no MST
				break;
			}

			const int u = q.begin()->v;
			const int x = q.begin()->w;
			s[u] = true;
			/* c += x; */
			q.erase(q.begin());

			if (m[u].v != -1) {
				const int v = m[u].v;
				o[u][v] = x;

				// skip this for directed graph
				o[v][u] = x;
			}

			for (const auto &[w, v] : g[u]) {
				if (!s[v] && w < m[v].w) {
					q.erase({m[v].w, v});
					m[v] = {w, u};
					q.insert({w, v});
				}
			}
		}
		return o;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
template <class T>
ostream &operator<<(ostream &out, const vector<T> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) {
		out << (i++ ? ", " : "");
		if (e == X)
			out << "x";
		else
			out << e;
	}
	out << "}";
	return out;
}

ostream &operator<<(ostream &out, const Graph &g)
{
	const int n = static_cast<int>(g.size());
	const string sp(6, ' ');
	out << "Graph nodes = " << n << ", edges:\n";
	out << sp << "{";
	for (int i = 0; i < n; i++) {
		if (i) out << sp << ' ';
		out << g[i];
		if (i < n - 1) out << ",\n";
	}
	out << "}";
	return out;
}

void test_impl(const vector<Graph> &ip, const vector<Graph> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		const string test = format("test-{}", i);
		Graph t = f->minSpanTree(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << ": " << test << " failed!\n"
			     << "  expected:\n"
			     << "    " << op[i] << "\n"
			     << "  actual:\n"
			     << "    " << t << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  " << test << ":  "
			     << "  input:\n"
			     << ip[i] << "\n"
			     << "  output:\n"
			     << t << "\n";
	}
}

Graph _edges2mat(const int n, const Graph &edges)
{
	// convert list of edges to adjacency matrix
	Graph g(n, vector<int>(n, X));
	for (size_t i = 0; i < edges.size(); i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		g[u][v] = w;

		// skip this for directed graph
		g[v][u] = w;
	}
	return g;
}

void _append_test_data_01(vector<Graph> &ip, vector<Graph> &op)
{
	const int n = 4;

	Graph edges{
	    {0, 1, 10},
	    {2, 3, 4},
	    {2, 0, 6},
	    {0, 3, 5},
	};

	Graph i = _edges2mat(n, edges);

	edges = {
	    {2, 3, 4},
	    {0, 3, 5},
	    {0, 1, 10},
	};

	Graph o = _edges2mat(n, edges);

	ip.push_back(i);
	op.push_back(o);
}

void _append_test_data_02(vector<Graph> &ip, vector<Graph> &op)
{
	const int n = 4;

	Graph edges{
	    {0, 1, 10}, {0, 2, 21}, {1, 2, 18}, {1, 3, 22}, {2, 3, 13},
	};

	Graph i = _edges2mat(n, edges);

	edges = {
	    {0, 1, 10},
	    {2, 3, 13},
	    {1, 2, 18},
	};

	Graph o = _edges2mat(n, edges);

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
	    make_shared<_01_prims_simple>(),
	    make_shared<_02_prims_dg>(),
	    make_shared<_02_prims_sg>(),
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
