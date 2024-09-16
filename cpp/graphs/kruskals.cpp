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

#include "tests.h"
#include "graphs.h"

using namespace Graphs;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
/* Function object to sort edges by weight in ascending order
 *
 * This is similar to std::less<Edge>() except it doesn't call
 * std::lexicographical_compare to avoid comparing sequentially instead
 * compare by weights of the edges.
 */
struct LessEdge {
	bool operator()(const vi_t &l, const vi_t &r) const
	{
		return l[2] < r[2];
	}
};

#define _kru_Simple_desc "Simple"

/* TC : O(n log n + n^2)
 * SC : O(V) => O(n)
 */
namespace Simple
{
vi2_t minSpanTree(int n, vi2_t &g)
{
	vi2_t o;
	vi_t p(n);
	iota(begin(p), end(p), 0);
	ranges::sort(g, LessEdge());

	/* int c = 0; */ // minimum cost
	for (const auto &ge : g) {
		int u = ge[0], v = ge[1], w = ge[2];
		int pu = p[u];
		int pv = p[v];
		if (pu == pv) continue;

		/* c += w; */
		o.push_back({u, v, w});

		for (int i = 0; i < n; i++) {
			if (p[i] == pu) p[i] = pv;
		}
	}
	return o;
}
} // namespace Simple

#define _kru_DisjointSetUnion_desc "Disjoint Set Union"

/* TC : O(n log n + alpha(n)) => O(n log n)
 *      where alpha(n) is the inverse Ackermann function => near O(1)
 * SC : O(V) => O(n)
 */
namespace DisjointSetUnion
{
struct DSU {
	vi_t parent, rank;

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

vi2_t minSpanTree(int n, vi2_t &g)
{
	DSU d(n);
	vi2_t o;

	fii (i, n) d.make_set(i);

	ranges::sort(g, LessEdge());

	/* int c = 0; */ // minimum cost
	for (const auto &ge : g) {
		int u = ge[0], v = ge[1], w = ge[2];
		if (d.find_set(u) == d.find_set(v)) continue;

		/* c += w; */
		o.push_back({u, v, w});
		d.union_sets(u, v);
	}
	return o;
}
} // namespace DisjointSetUnion

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _kru_check(n, ed, e, _ns)                                            \
	{                                                                    \
		vi2_t a = _ns::minSpanTree(n, ed);                           \
		string im = to_string(n, ed);                                \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(im, a);                                          \
	}

#define _kru_desc_prefix "Kruskal's Minimum Spanning Tree"

#define _KRU_NAME(var) var
#define _KRU_DESC(var) _kru_desc_prefix " - " _kru_##var##_desc

#define _KRU_TEST(var)                                                       \
	TEST(_KRU_NAME(var), _KRU_DESC(var))                                 \
	{                                                                    \
		vi_t _nodes = {4, 4};                                        \
		vector<vi2_t> _edges;                                        \
		_edges.push_back({{0, 1, 10},                                \
		                  {1, 3, 15},                                \
		                  {2, 3, 4},                                 \
		                  {2, 0, 6},                                 \
		                  {0, 3, 5}});                               \
		_edges.push_back({{0, 1, 10},                                \
		                  {0, 2, 21},                                \
		                  {1, 2, 18},                                \
		                  {1, 3, 22},                                \
		                  {2, 3, 13}});                              \
		vector<vi2_t> _e;                                            \
		_e.push_back({{2, 3, 4}, {0, 3, 5}, {0, 1, 10}});            \
		_e.push_back({{0, 1, 10}, {2, 3, 13}, {1, 2, 18}});          \
		int n = size(_nodes);                                        \
		fii (i, n) {                                                 \
			_kru_check(_nodes[i], _edges[i], _e[i],              \
			           _KRU_NAME(var));                          \
		}                                                            \
	}

_KRU_TEST(Simple);
_KRU_TEST(DisjointSetUnion);

INIT_TEST_MAIN();
