/**
 * Maximum subarray sum
 * ====================
 * 
 * Refer:
 *
 * [lc53]: https://leetcode.com/problems/maximum-subarray/
 * [bd1]: https://www.baeldung.com/java-maximum-subarray
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _mss_BruteForce_desc "Brute Force"

/* TC : O(n^2) => For trying all possible n*(n+1)/2 sub arrays
 * SC : O(1)
 */
namespace BruteForce
{
vi_t maxSubArray(const vi_t &a)
{
	int n = size(a), s = INT_MIN, b = 0, e = 0;
	fii (i, n) {
		int c = 0;
		for (int j = i; j < n; j++) {
			c += a[j];
			if (c > s) {
				s = c;
				b = i;
				e = j;
			}
		}
	}
	/* FIXME Get pointers to the subarry in other implementations. */
	b = 0, e = 0;
	return {b, e, s};
}
}; // namespace BruteForce

#define _mss_Recursive_desc "Recursive"

/* TC : O(n^2) => For trying all possible n*(n+1)/2 sub arrays
 * SC : O(n)   => For recursion
 */
namespace Recursive
{
int solve(const vi_t &a, int i, bool pick)
{
	int n = size(a);
	if (i >= n) return (pick ? 0 : INT_MIN);
	if (pick) return max(0, a[i] + solve(a, i + 1, true));
	return max(solve(a, i + 1, false), a[i] + solve(a, i + 1, true));
}

vi_t maxSubArray(const vi_t &a)
{
	int s, b = 0, e = 0;
	s = solve(a, 0, false);
	return {b, e, s};
}
} // namespace Recursive

#define _mss_DP_Memo_desc "Dynamic Programming memoization"

/* TC : O(n) => For calculating 2n states and reusing memos
 * SC : O(n) => For recursion
 */
namespace DP_Memo
{
int solve(const vi_t &a, int i, bool pick, vi2_t &dp)
{
	int n = size(a);
	if (i >= n) return (pick ? 0 : INT_MIN);
	if (dp[pick][i] != -1) return dp[pick][i];
	if (pick)
		return dp[pick][i] = max(0, a[i] + solve(a, i + 1, true, dp));
	return dp[pick][i] = max(solve(a, i + 1, false, dp),
	                         a[i] + solve(a, i + 1, true, dp));
}

vi_t maxSubArray(const vi_t &a)
{
	int n = size(a), s, b = 0, e = 0;
	vi2_t dp(2, vi_t(n, -1));
	s = solve(a, 0, false, dp);
	return {b, e, s};
}
}; // namespace DP_Memo

#define _mss_DP_Tab_desc "Dynamic Programming tabulation"

/* TC : O(n)
 * SC : O(n) => For dp table
 */
namespace DP_Tab
{
vi_t maxSubArray(const vi_t &a)
{
	int n = size(a), s, b = 0, e = 0;
	vi_t dp(a);
	for (int i = 1; i < n; i++) dp[i] = max(a[i], a[i] + dp[i - 1]);
	s = *max_element(begin(dp), end(dp));
	return {b, e, s};
}
} // namespace DP_Tab

#define _mss_Kadanes_desc "Kadane's algorithm"

/**
 * TC : O(n)
 * SC : O(1)
 */
namespace Kadanes
{
vi_t maxSubArray(const vi_t &a)
{
	int n = size(a), c = 0, s = INT_MIN, b = 0, e = 0, j = 0;
	fii (i, n) {
		c += a[i];
		if (c > s) {
			s = c;
			b = j;
			e = i;
		}

		if (c < 0) {
			c = 0;
			j = i + 1;
		}
	}
	/* FIXME Get pointers to the subarry in other implementations. */
	b = 0, e = 0;
	return {b, e, s};
}
} // namespace Kadanes

#define _mss_DivideConquer_desc "Divide & Conquer"

/**
 * TC : O(n log n)
 * SC : O(log n)
 *
 * Recurrence relation for this method T(n) = 2T(n/2) + O(n) as:
 *
 * - Recurring for left and right half (2T(n/2)).
 * - Calculating maximum subarray sum O(n).
 *
 * Solving this recurrence using master theorem to get TC O(n log n)
 */
namespace DivideConquer
{
int solve(const vi_t &a, int l, int r)
{
	if (l > r) return INT_MIN;
	int m = (l + r) / 2, lsum = 0, rsum = 0;

	for (int i = m - 1, c = 0; i >= l; i--) {
		c += a[i];
		lsum = max(lsum, c);
	}

	for (int i = m + 1, c = 0; i <= r; i++) {
		c += a[i];
		rsum = max(rsum, c);
	}

	return max(
	    {solve(a, l, m - 1), solve(a, m + 1, r), lsum + a[m] + rsum});
}

vi_t maxSubArray(const vi_t &a)
{
	int n = size(a), s, b = 0, e = 0;
	s = solve(a, 0, n - 1);
	return {b, e, s};
}
} // namespace DivideConquer

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _mss_check(i, e)                                                     \
	{                                                                    \
		vi_t a = maxSubArray(i);                                     \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _mss_desc_prefix "Maximum Subarray Sum"

#define _MSS_NAME(var) var
#define _MSS_DESC(var) _mss_desc_prefix " - " _mss_##var##_desc

#define _MSS_TEST(var)                                                       \
	TEST(_MSS_NAME(var), _MSS_DESC(var))                                 \
	{                                                                    \
		using namespace _MSS_NAME(var);                              \
		vi2_t ip{                                                    \
		    {-2, 1, -3, 4, -1, 2, 1, -5, 4},                         \
		    {1},                                                     \
		    {5, 4, -1, 7, 8},                                        \
		};                                                           \
		vi2_t op{                                                    \
		    {0, 0, 6},                                               \
		    {0, 0, 1},                                               \
		    {0, 0, 23},                                              \
		};                                                           \
		int n = size(ip);                                            \
		fii (i, n) _mss_check(ip[i], op[i]);                         \
	}

_MSS_TEST(BruteForce);
_MSS_TEST(Recursive);
_MSS_TEST(DP_Memo);
_MSS_TEST(DP_Tab);
_MSS_TEST(Kadanes);
_MSS_TEST(DivideConquer);

INIT_TEST_MAIN();
