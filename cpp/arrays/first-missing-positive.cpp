/**
 * First Missing Positive
 * ======================
 *
 * Refer:
 *
 * https://leetcode.com/problems/first-missing-positive/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _fmp_desc "First missing positive"

/* TC : O(n)
 * SC : O(1)
 */
int firstMissingPositive(vi_t &a)
{
	int n = size(a);
	fii (i, n)
		while (a[i] > 0 && a[i] <= n && a[a[i] - 1] != a[i])
			swap(a[i], a[a[i] - 1]);

	fii (i, n)
		if (a[i] != i + 1) return i + 1;
	return n + 1;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _fmp_check(i, e)                                                     \
	{                                                                    \
		vi_t t = i;                                                  \
		int a = firstMissingPositive(t);                             \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

TEST(firstMissingPositive, _fmp_desc)
{
	vi2_t ip{
	    {1, 2, 0},
	    {3, 4, -1, 1},
	    {7, 8, 9, 11, 12},
	};
	vi_t op{3, 2, 1};
	int n = size(ip);
	fii (i, n) _fmp_check(ip[i], op[i]);
}

INIT_TEST_MAIN();
