/**
 * Binary Search - 03
 * ==================
 *
 * Binary search in sorted rotated array with duplicates.
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

#define _bs_desc "Binary search in sorted rotated array with duplicates"

/* TC : Best O(1), Average O(log n), Worst O(log n)
 * SC : O(1)
 */
bool search(const vi_t &a, int t)
{
	int n = size(a), l = 0, r = n - 1;
	while (l <= r) {
		int m = (l + r) / 2;
		if (t == a[m]) return true;
		if (a[l] == a[m] && a[m] == a[r]) {
			l++, r--;
			continue;
		}
		if (a[l] <= a[m]) {
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
	return false;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _bs_check(arr, target, e)                                            \
	{                                                                    \
		bool a = search(arr, target);                                \
		string im = format("array = {}, target = {}",                \
		                   to_string(arr), target);                  \
		string om = a ? "true" : "false";                            \
		SET_CUSTOM_SUCCESS_MSG(im, om);                              \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(im, a);                                          \
	}

TEST(search, _bs_desc)
{
	vi2_t arrs{
	    {4, 5, 6, 7, 0, 1, 2},
	    {2, 5, 6, 0, 0, 1, 2},
	    {1},
	    {3, 1, 2, 3, 3, 3, 3},
	};
	vi_t targets{0, 3, 0, 1};
	vi_t exps{true, false, false, true};
	int n = size(arrs);
	fii (i, n) _bs_check(arrs[i], targets[i], exps[i]);
}

INIT_TEST_MAIN();
