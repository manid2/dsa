/**
 * Box stacking - 01
 * =================
 *
 * Refer:
 *
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
bool check(const vi_t &p, const vi_t &c)
{
	return (p[0] <= c[0] && p[1] <= c[1] && p[2] <= c[2]);
}

#define _bs1_Recursive_desc "Recursive"

/* TC : O(n log n + 2^n)
 * SC : O(n)
 */
namespace Recursive
{
int solve(vi2_t &a, int p, int c);

int maxHeight(vi2_t &a)
{
	for (auto &c : a) ranges::sort(c);
	ranges::sort(a);
	return solve(a, -1, 0);
}

int solve(vi2_t &a, int p, int c)
{
	int n = size(a);
	if (c == n) return 0;
	int pick = INT_MIN;
	if (p == -1 || check(a[p], a[c])) {
		pick = a[c][2] + solve(a, c, c + 1);
	}
	int skip = solve(a, p, c + 1);
	return max(pick, skip);
}
} // namespace Recursive

#define _bs1_DP_Tab_desc "Dynamic Programming tabulation"

/* TC : O(n^2)
 * SC : O(n^2)
 */
namespace DP_Tab
{
int maxHeight(vi2_t &a)
{
	for (auto &c : a) ranges::sort(c);
	ranges::sort(a);
	int n = size(a);
	vi2_v(dp, n + 1, 0);
	frii (i, n - 1) {
		for (int j = i - 1; j >= -1; j--) {
			int pick = INT_MIN;
			if (j == -1 || check(a[j], a[i])) {
				pick = a[i][2] + dp[i + 1][i + 1];
			}
			int skip = dp[i + 1][j + 1];
			dp[i][j + 1] = max(pick, skip);
		}
	}
	return dp[0][0];
}
} // namespace DP_Tab

#define _bs1_DP_Tab2_desc "Dynamic Programming tabulation space optimized"

/* TC : O(n^2)
 * SC : O(n)
 */
namespace DP_Tab2
{
int maxHeight(vi2_t &a)
{
	for (auto &c : a) ranges::sort(c);
	ranges::sort(a);
	int n = size(a);
	vi_t last(n + 1, 0), curr(n + 1, 0);
	frii (i, n - 1) {
		for (int j = i - 1; j >= -1; j--) {
			int pick = INT_MIN;
			if (j == -1 || check(a[j], a[i])) {
				pick = a[i][2] + last[i + 1];
			}
			int skip = last[j + 1];
			curr[j + 1] = max(pick, skip);
		}
		last = curr;
	}
	return last[0];
}
} // namespace DP_Tab2

#define _bs1_DP_Tab3_desc "Dynamic Programming tabulation simple"

/* TC : O(n^2)
 * SC : O(n)
 */
namespace DP_Tab3
{
int maxHeight(vi2_t &a)
{
	for (auto &c : a) ranges::sort(c);
	a.push_back({0, 0, 0});
	ranges::sort(a);
	int n = size(a), r = 0;
	vi_v(dp, n, 0);
	for (int i = 1; i < n; i++)
		fii (j, i)
			if (check(a[j], a[i])) {
				dp[i] = max(dp[i], dp[j] + a[i][2]);
				r = max(r, dp[i]);
			}
	return r;
}
} // namespace DP_Tab3

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _bs1_desc_prefix "Box stacking 01"

#define _BS1_NAME(var) var
#define _BS1_DESC(var) _bs1_desc_prefix " - " _bs1_##var##_desc

#define _BS1_TEST(var)                                                       \
	TEST(_BS1_NAME(var), _BS1_DESC(var))                                 \
	{                                                                    \
		using namespace _BS1_NAME(var);                              \
		int e, a;                                                    \
		vi2_t i, t;                                                  \
		i = {{50, 45, 20}, {95, 37, 53}, {45, 23, 12}};              \
		t = i;                                                       \
		e = 190;                                                     \
		a = maxHeight(t);                                            \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
                                                                             \
		i = {{38, 25, 45}, {76, 35, 3}};                             \
		t = i;                                                       \
		e = 76;                                                      \
		a = maxHeight(t);                                            \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

_BS1_TEST(Recursive);
_BS1_TEST(DP_Tab);
_BS1_TEST(DP_Tab2);
_BS1_TEST(DP_Tab3);

INIT_TEST_MAIN();
