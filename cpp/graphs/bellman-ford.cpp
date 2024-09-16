/**
 * Bellman-Ford - Single source shortest path to all nodes
 * =======================================================
 *
 * Refer:
 *
 * https://www.w3schools.com/dsa/dsa_algo_graphs_bellmanford.php
 * https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
 */

#include "tests.h"
#include "graphs.h"

using namespace Graphs;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _bf_desc "Bellman-Ford - Single source shortest path to all nodes"

/* TC : Best O(E), Average O(V*E), Worst O(V*E) => O(n^3) when E = V^2
 *      For a complete graph E = V(V-1)/2 => O(E) = O(V^2).
 * SC : O(V) => O(n)
 */
vi_t shortestPaths(int nodes, const vi2_t &edges, int source)
{
	int ne = size(edges);
	vi_t d(nodes, X);
	d[source] = 0;
	fii (i, (nodes - 1)) {
		fii (j, ne) {
			int u = edges[j][0];
			int v = edges[j][1];
			int w = edges[j][2];
			if (d[u] != X) d[v] = min(d[v], d[u] + w);
		}
	}
	// Detect negative cycle
	fii (j, ne) {
		int u = edges[j][0];
		int v = edges[j][1];
		int w = edges[j][2];
		if (d[u] != X && d[v] > d[u] + w) return {NX};
	}
	return d;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _bf_check(n, ed, s, e)                                               \
	vi_t a = shortestPaths(n, ed, s);                                    \
	string _pre("distances"), im, am;                                    \
	im += to_string(n, ed);                                              \
	im += format(", source = {}", s);                                    \
	am = format("{} = {}", _pre, to_string(a));                          \
	CHECK_EQ(e, a);                                                      \
	SHOW_OUTPUT(im, am);

TEST(shortestPaths, _bf_desc)
{
	vi_t _nodes = {4, 5, 5};
	vi_t _sources = {0, 0, 0};
	vector<vi2_t> _edges;
	_edges.push_back({{2, 1, -10}, {3, 2, 3}, {0, 3, 5}, {0, 1, 4}});
	_edges.push_back({{0, 1, -1},
	                  {0, 2, 3},
	                  {1, 2, 3},
	                  {1, 3, 2},
	                  {1, 4, 2},
	                  {3, 2, 5},
	                  {3, 1, 1},
	                  {4, 3, -3}});
	vi2_t nge = _edges[0];
	nge.push_back({1, 3, 5}); // Negative cycle edge in graph
	_edges.push_back(nge);

	vi2_t _distances = {
	    {0, -2, 8, 5},
	    {0, -1, 2, -2, 1},
	    {NX}, // When graph has negative cycle
	};

	int n = size(_nodes);
	fii (i, n) {
		_bf_check(_nodes[i], _edges[i], _sources[i], _distances[i]);
	}
}

INIT_TEST_MAIN();
