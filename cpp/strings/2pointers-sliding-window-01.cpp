/**
 * Two pointers - sliding window technique - 01
 * ============================================
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

#define _2p_sw_maxSubstrUniqChars_desc "Two Pointers - Sliding Window - "    \
        "Longest Substring Without Repeating Characters"

int maxSubstrUniqChars(const string &s)
{
	int n = size(s);
	int l = 0, r = 0, d = 0;
	vi_v(m, 128, 0);
	while (l < n && r < n) {
		if (!m[s[r]]++) r++, d = max(d, r - l);
		else m[s[l++]] = 0;
	}
	return d;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _2p_sw_maxSubstrUniqChars_check(i, e)                                \
	{                                                                    \
		int a = maxSubstrUniqChars(i);                               \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

TEST(maxSubstrUniqChars, _2p_sw_maxSubstrUniqChars_desc)
{
	vector<string> ip{"", "abcabcbb", "bbbbb", "pwwkew"};
	vector<int> op{0, 3, 1, 3};
	int n = size(ip);
	fii (i, n) _2p_sw_maxSubstrUniqChars_check(ip[i], op[i]);
}

INIT_TEST_MAIN();