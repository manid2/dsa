/**
 * Non-overlapping Intervals
 * =========================
 *
 * Refer:
 * 
 * https://leetcode.com/problems/non-overlapping-intervals/
 * https://medium.com/swlh/non-overlapping-intervals-f0bce2dfc617
 */

#include <tests.h>

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _noi_desc "Non-overlapping Intervals - Greedy"

/**
 * TC: O(n log n + n)
 * SC: O(1)
 */
namespace Greedy
{
int eraseOverlapIntervals(vi2_t &a)
{
	ranges::sort(a, [](vi_t &l, vi_t &r) { return l[0] < r[0]; });
	int n = size(a), c = 0;
	for (int i = 0, j = 1; j < n; j++) {
		if (a[i][1] > a[j][0]) {
			c++;
			if (a[i][1] > a[j][1]) i = j;
		} else {
			i = j;
		}
	}
	return c;
}
} // namespace Greedy

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _noi_check(i, e)                                                     \
	{                                                                    \
		using namespace Greedy;                                      \
		vi2_t t = i;                                                 \
		int a = eraseOverlapIntervals(t);                            \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

TEST(eraseOverlapIntervals, _noi_desc)
{
	vector<vi2_t> ip{
	    {{1, 2}, {2, 3}, {3, 4}, {1, 3}},
	    {{1, 20}, {2, 3}, {3, 4}, {1, 3}, {4, 5}},
	};
	vi_t op{1, 2};
	int n = size(ip);
	fii (i, n) _noi_check(ip[i], op[i]);
}

INIT_TEST_MAIN();
