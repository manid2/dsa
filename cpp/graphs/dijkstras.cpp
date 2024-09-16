/**
 * Dijkstra's - Single source shortest path to all nodes
 * =====================================================
 *
 * Refer:
 *
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * https://github.com/wj32/Judge/blob/master/HackerRank/Dijkstra-%20Shortest%20Reach%202.cpp
 * https://takeuforward.org/data-structure/dijkstras-algorithm-shortest-distance/
 * https://cp-algorithms.com/graph/dijkstra.html
 */

#include "tests.h"
#include "graphs.h"

using namespace Graphs;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _dij_MaxHeap_desc "Using max heap (priority queue)"

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
namespace MaxHeap
{
/* Graph is adjacency list with list of pairs of adjacent nodes & weight */
void dijkstras(const v2pi_t &g, int s, vi_t &d, vi_t &p)
{
	using pq_t = priority_queue<pii_t, vpi_t, greater<pii_t>>; // max heap

	const int n = size(g);
	d.assign(n, X);  // distances
	p.assign(n, -1); // predecessors

	pq_t pq;
	pq.emplace(0, s);
	d[s] = 0;

	while (!pq.empty()) {
		int x = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		if (x > d[u]) continue;

		for (auto an : g[u]) {
			int v = an.first;
			int w = an.second;

			if (d[v] > x + w) {
				d[v] = x + w;
				p[v] = u;
				pq.emplace(d[v], v);
			}
		}
	}
}

void shortestPaths(int nodes, const vi2_t &edges, int source, vi_t &distances,
                   vi_t &parent)
{
	// use n + 1 for 1 indexed nodes
	v2pi_t g(nodes);
	fsi (i, size(edges)) {
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		g[u].emplace_back(v, w);

		// skip this for directed graph
		g[v].emplace_back(u, w);
	}
	dijkstras(g, source, distances, parent);
}
}; // namespace MaxHeap

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _dij_check_eq_fail(e, a, _pre)                                       \
	{                                                                    \
		string em, am;                                               \
		em = format("{} = {}", _pre, to_string(e));                  \
		am = format("{} = {}", _pre, to_string(a));                  \
		SET_CUSTOM_FAIL_MSG(em, am);                                 \
		FAIL();                                                      \
	}

#define _dij_check_eq(_d, d, _p, p, _p2, p2)                                 \
	if (_d != d) _dij_check_eq_fail(_d, d, "distances");                 \
	if (_p != p) _dij_check_eq_fail(_p, p, "parent");                    \
	if (_p2 != p2) _dij_check_eq_fail(_p2, p2, "path");                  \
	SUCCESS();

#define _dij_show_output(n, ed, s, t, d, p, p2)                              \
	{                                                                    \
		string im, om;                                               \
		im += to_string(n, ed) + ", ";                               \
		im += format("source = {}, target = {}", s, t);              \
		om += format("distances = {}, parent = {}, path = {}",       \
		             to_string(d), to_string(p), to_string(p2));     \
		SHOW_OUTPUT(im, om);                                         \
	}

#define _dij_check(n, ed, s, t, _d, _p, _p2, _ns)                            \
	{                                                                    \
		vi_t d, p, p2;                                               \
		_ns::shortestPaths(n, ed, s, d, p);                          \
		p2 = shortestPath(p, s, t);                                  \
		_dij_check_eq(_d, d, _p, p, _p2, p2);                        \
		_dij_show_output(n, ed, s, t, d, p, p2);                     \
	}

#define _dij_desc_prefix "Dijkstra's single source shortest path to all"

#define _DIJ_NAME(var) var
#define _DIJ_DESC(var) _dij_desc_prefix " - " _dij_##var##_desc

#define _DIJ_TEST(var)                                                       \
	TEST(_DIJ_NAME(var), _DIJ_DESC(var))                                 \
	{                                                                    \
		vi_t _nodes = {5, 4};                                        \
		vi_t _sources = {0, 0};                                      \
		vi_t _targets = {4, 3};                                      \
		vector<vi2_t> _edges;                                        \
		_edges.push_back({{0, 1, 2},                                 \
		                  {0, 3, 1},                                 \
		                  {1, 2, 4},                                 \
		                  {1, 4, 5},                                 \
		                  {2, 3, 3},                                 \
		                  {2, 4, 1}});                               \
		_edges.push_back(                                            \
		    {{0, 1, 24}, {0, 3, 20}, {2, 0, 3}, {3, 2, 12}});        \
                                                                             \
		vi2_t _distances = {{0, 2, 4, 1, 5}, {0, 24, 3, 15}};        \
		vi2_t _parent = {{-1, 0, 3, 0, 2}, {-1, 0, 0, 2}};           \
		vi2_t _paths = {{0, 3, 2, 4}, {0, 2, 3}};                    \
                                                                             \
		int n = size(_nodes);                                        \
		fii (i, n) {                                                 \
			_dij_check(_nodes[i], _edges[i], _sources[i],        \
			           _targets[i], _distances[i], _parent[i],   \
			           _paths[i], _DIJ_NAME(var));               \
		}                                                            \
	}

_DIJ_TEST(MaxHeap);

INIT_TEST_MAIN();
