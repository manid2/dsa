/**
 * Two sum - 01
 * ============
 *
 * Refer:
 *
 * https://leetcode.com/problems/two-sum/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _2sum_desc "Two sum - sum of 2 numbers in array to get target"

/* TC : O(n)
 * SC : O(n)
 */
vi_t twoSum(const vi_t &a, int t)
{
	int n = a.size();
	umi_t m;
	fii (i, n) {
		int c = t - a[i];
		if (m.contains(c)) return {m[c], i};
		m[a[i]] = i;
	}
	return {};
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _2sum_check(i, t, e)                                                 \
	{                                                                    \
		vi_t a = twoSum(i, t);                                       \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a)                                            \
	}

TEST(twoSum, _2sum_desc)
{
	vi_t i, e;

	i = {2, 7, 11, 15};
	e = {0, 1};
	_2sum_check(i, 9, e);

	i = {3, 2, 4};
	e = {1, 2};
	_2sum_check(i, 6, e);

	i = {3, 3};
	e = {0, 1};
	_2sum_check(i, 6, e);
}

INIT_TEST_MAIN();
