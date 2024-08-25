/**
 * Binary Search - 01
 * ==================
 *
 * Binary search algorithm with worst case TC O(log n).
 *
 * Refer:
 *
 * https://leetcode.com/problems/binary-search/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _bs_desc "Binary search"

/* TC : Best O(1), Average O(log n), Worst O(log n)
 * SC : O(1)
 */
int search(const vi_t &a, int t)
{
	int n = size(a), l = 0, r = n - 1;
	while (l <= r) {
		int m = (l + r) / 2;
		if (t == a[m])
			return m;
		else if (t < a[m])
			r = m - 1;
		else
			l = m + 1;
	}
	return -1;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _bs_check(arr, target, e)                                            \
	{                                                                    \
		int a = search(arr, target);                                 \
		string im = format("array = {}, target = {}",                \
		                   to_string(arr), target);                  \
		SET_CUSTOM_SUCCESS_MSG(im, to_string(a));                    \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(im, a);                                          \
	}

TEST(search, _bs_desc)
{
	vi2_t arrs{
	    {-1, 0, 3, 5, 9, 12},
	    {-1, 0, 3, 5, 9, 12},
	};
	vi_t targets{9, 2};
	vi_t exps{4, -1};
	int n = size(arrs);
	fii (i, n) _bs_check(arrs[i], targets[i], exps[i]);
}

INIT_TEST_MAIN();
