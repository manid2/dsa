/**
 * Binary Search - 02
 * ==================
 *
 * Binary search in sorted rotated array.
 *
 * Refer:
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _bs_desc "Binary search in sorted rotated array"

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
		else if (a[l] <= a[m]) {
			if (a[l] <= t && t < a[m])
				r = m - 1;
			else
				l = m + 1;
		} else {
			if (a[m] < t && t <= a[r])
				l = m + 1;
			else
				r = m - 1;
		}
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
	    {4, 5, 6, 7, 0, 1, 2},
	    {4, 5, 6, 7, 0, 1, 2},
	    {1},
	};
	vi_t targets{0, 3, 0};
	vi_t exps{4, -1, -1};
	int n = size(arrs);
	fii (i, n) _bs_check(arrs[i], targets[i], exps[i]);
}

INIT_TEST_MAIN();
