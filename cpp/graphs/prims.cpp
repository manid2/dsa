/**
 * Prim's - Minimum Spanning Tree
 * ==============================
 *
 * Refer:
 *
 * https://cp-algorithms.com/graph/mst_prim.html
 * https://www.programiz.com/dsa/prim-algorithm
 */

#include "tests.h"
#include "graphs.h"

using namespace Graphs;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _pri_Simple_desc "Simple"

/* TC : O(n^3)
 * SC : O(V) => O(n)
 */
namespace Simple
{
// Graph is a V * V matrix where V is number of nodes
vi2_t minSpanTree(const vi2_t &g)
{
	const int n = size(g);
	vi2_v(o, n, X);
	vector<bool> s(n, false); // selected nodes

	int u, v, w, e = 0 /* c = 0 // min cost */;
	while (e++ < n) {
		u = v = 0, w = X;
		for (int i = 0; i < n; i++) {
			if (!s[i]) continue;
			for (int j = 0; j < n; j++) {
				const int gw = g[i][j];
				if (s[j] || gw == X || w < gw) continue;
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
} // namespace Simple

#define _pri_DenseGraphs_desc "Dense Graphs"

// Edge is a pair of weight & to node
struct Edge {
	int w = X, v = -1;

	bool operator<(const Edge &r) const
	{
		return make_pair(w, v) < make_pair(r.w, r.v);
	}
};

// Graph is adjacency list
#define ve_t  vector<Edge>
#define ve2_t vector<ve_t>

/* TC : O(n^2)
 * SC : O(V) => O(n)
 */
namespace DenseGraphs
{
vi2_t minSpanTree(const vi2_t &g)
{
	const int n = size(g);
	vi2_v(o, n, X);
	vector<bool> s(n, false); // selected nodes

	/* Minimum weight edge to a selected node for each not yet selected
	 * node. */
	ve_t m(n);
	m[0].w = 0;

	/* int c = 0; */ // minimum cost
	for (int i = 0; i < n; i++) {
		int u = -1;
		for (int j = 0; j < n; j++) {
			if (!s[j] && (u == -1 || m[j].w < m[u].w)) u = j;
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
} // namespace DenseGraphs

#define _pri_SparseGraphs_desc "Sparse Graphs"

/* TC : O(n log n)
 * SC : O(V) => O(n)
 */
namespace SparseGraphs
{
vi2_t primsSparse(const ve2_t &g)
{
	const int n = size(g);
	vi2_v(o, n, X);
	vector<bool> s(n, false); // selected nodes

	/* Minimum weight edge to a selected node for each not yet selected
	 * node. */
	ve_t m(n);
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

vi2_t minSpanTree(const vi2_t &g)
{
	const int n = size(g);
	// convert to adjacency list
	ve2_t a(n);
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++) {
			const int w = g[u][v];
			if (w != X) a[u].push_back({w, v});
		}
	return primsSparse(a);
}
}; // namespace SparseGraphs

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _pri_check(i, e, _ns)                                                \
	{                                                                    \
		vi2_t a = _ns::minSpanTree(i);                               \
		CHECK_EQ(e, a);                                              \
		string _pre("Adjacency matrix"), im, am;                     \
		im = format("{} = {}", _pre, to_string(i));                  \
		am = format("{} = {}", _pre, to_string(a));                  \
		SHOW_OUTPUT(im, am);                                         \
	}

#define _pri_desc_prefix "Prim's Minimum Spanning Tree"

#define _PRI_NAME(var) var
#define _PRI_DESC(var) _pri_desc_prefix " - " _pri_##var##_desc

#define _PRI_TEST(var)                                                       \
	TEST(_PRI_NAME(var), _PRI_DESC(var))                                 \
	{                                                                    \
		vector<vi2_t> _g;                                            \
		_g.push_back(edges2mat(4, {                                  \
		                              {0, 1, 10},                    \
		                              {2, 3, 4},                     \
		                              {2, 0, 6},                     \
		                              {0, 3, 5},                     \
		                          }));                               \
		_g.push_back(edges2mat(4, {                                  \
		                              {0, 1, 10},                    \
		                              {0, 2, 21},                    \
		                              {1, 2, 18},                    \
		                              {1, 3, 22},                    \
		                              {2, 3, 13},                    \
		                          }));                               \
		vector<vi2_t> _e;                                            \
		_e.push_back(edges2mat(4, {                                  \
		                              {2, 3, 4},                     \
		                              {0, 3, 5},                     \
		                              {0, 1, 10},                    \
		                          }));                               \
		_e.push_back(edges2mat(4, {                                  \
		                              {0, 1, 10},                    \
		                              {2, 3, 13},                    \
		                              {1, 2, 18},                    \
		                          }));                               \
		int n = size(_g);                                            \
		fii (i, n) { _pri_check(_g[i], _e[i], _PRI_NAME(var)); }     \
	}

_PRI_TEST(Simple);
_PRI_TEST(DenseGraphs);
_PRI_TEST(SparseGraphs);

INIT_TEST_MAIN();
