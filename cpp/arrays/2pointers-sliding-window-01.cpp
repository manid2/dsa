/**
 * Two pointers - sliding window technique - 01
 * ============================================
 *
 * This technique is used to find subarrays or substrings given a set of
 * conditions.
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/window-sliding-technique/
 * https://discuss.leetcode.com/topic/30941/here-is-a-10-line-template-that-can-solve-most-substring-problems
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
#define _2p_sw_maxSumKConseq_desc                                            \
	"Two Pointers - Sliding Window - "                                   \
	"Maximum sum of K consequent elements"

int maxSumKConseq(const vi_t &a, int k)
{
	int n = size(a);
	int r = 0, c = 0;
	fii (i, k) r += a[i];
	c = r;
	for (int i = k; i < n; i++) {
		c += a[i] - a[i - k];
		r = max(r, c);
	}
	return r;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _2p_sw_maxSumKConseq_check(i, k, e)                                  \
	{                                                                    \
		int a = maxSumKConseq(i, k);                                 \
		CHECK_EQ(e, a);                                              \
		string im = format("array = {}, k = {}", to_string(i), k);   \
		SET_CUSTOM_SUCCESS_MSG(im, to_string(a));                    \
		SHOW_OUTPUT(i, a);                                           \
	}

TEST(maxSumKConseq, _2p_sw_maxSumKConseq_desc)
{
	vi2_t _a{
	    {100, 200, 300, 400},
	    {1, 4, 2, 10, 23, 3, 1, 0, 20},
	};
	vi_t _k{2, 4};
	vi_t _e{700, 39};
	int n = size(_a);
	fii (i, n) _2p_sw_maxSumKConseq_check(_a[i], _k[i], _e[i]);
}

INIT_TEST_MAIN();
