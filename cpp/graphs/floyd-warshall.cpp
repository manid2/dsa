/**
 * Floyd-Warshall - All pairs shortest paths
 * =========================================
 *
 * Refer:
 *
 * https://www.programiz.com/dsa/floyd-warshall-algorithm
 */

#include "tests.h"
#include "graphs.h"

using namespace Graphs;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _fw_desc "Floyd-Warshall - All pairs shortest paths"

// Graph is a V * V matriX where V is number of nodes
/* TC : O(V^3)
 * SC : O(V^2)
 */
void _update(vi2_t &g, int k, int i, int j)
{
	if (g[i][k] != X && g[k][j] != X)
		g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}

void shortestPaths(vi2_t &g)
{
	const int n = size(g);
	fii (k, n) {
		fii (i, n) {
			fii (j, n) _update(g, k, i, j);
		}
	}
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _fw_check_eq(e, a, _pre, am)                                         \
	{                                                                    \
		string em;                                                   \
		em = format("{} = {}", _pre, to_string(e));                  \
		if (e != a) {                                                \
			SET_CUSTOM_FAIL_MSG(em, am);                         \
			FAIL();                                              \
		}                                                            \
		SUCCESS();                                                   \
	}

#define _fw_check(i, e)                                                      \
	{                                                                    \
		vi2_t a = i;                                                 \
		shortestPaths(a);                                            \
		string _pre("Adjacency matrix"), im, am;                     \
		im = format("{} = {}", _pre, to_string(i));                  \
		am = format("{} = {}", _pre, to_string(a));                  \
		_fw_check_eq(e, a, _pre, am);                                \
		SHOW_OUTPUT(im, am);                                         \
	}

TEST(shortestPaths, _fw_desc)
{
	vector<vi2_t> _i{
	    {
	        {0, 3, X, 7},
	        {8, 0, 2, X},
	        {5, X, 0, 1},
	        {2, X, X, 0},
	    },
	    {
	        {0, 5, X, 10},
	        {X, 0, 3, X},
	        {X, X, 0, 1},
	        {X, X, X, 0},
	    },
	    {
	        {0, 3, X, 5},
	        {2, 0, X, 4},
	        {X, 1, 0, X},
	        {X, X, 2, 0},
	    },
	};
	vector<vi2_t> _e{
	    {
	        {0, 3, 5, 6},
	        {5, 0, 2, 3},
	        {3, 6, 0, 1},
	        {2, 5, 7, 0},
	    },
	    {
	        {0, 5, 8, 9},
	        {X, 0, 3, 4},
	        {X, X, 0, 1},
	        {X, X, X, 0},
	    },
	    {
	        {0, 3, 7, 5},
	        {2, 0, 6, 4},
	        {3, 1, 0, 5},
	        {5, 3, 2, 0},
	    },
	};
	int n = size(_i);
	fii (i, n) _fw_check(_i[i], _e[i]);
}

INIT_TEST_MAIN();
