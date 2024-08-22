/**
 * Box stacking - 02
 * =================
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/box-stacking-problem-dp-22/
 * https://leetcode.com/discuss/interview-question/3551334/Box-Stacking
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
bool check(const vi_t &p, const vi_t &c)
{
	return (p[0] < c[0] && p[1] < c[1]);
}

vi2_t rotate(const vi2_t &a)
{
	int n = size(a);
	vi2_t r;
	for (int i = 0; i < n; i++) {
		int w = a[i][0];
		int l = a[i][1];
		int h = a[i][2];
		r.push_back({w, l, h});
		r.push_back({w, h, l});
		r.push_back({l, h, w});
		r.push_back({l, w, h});
		r.push_back({h, w, l});
		r.push_back({h, l, w});
	}
	return r;
}

#define _bs2_Recursive_desc "Recursive"

/* TC : O(n log n + 2^n)
 * SC : O(n)
 */
namespace Recursive
{
int solve(vi2_t &a, int p, int c);

int maxHeight(vi2_t &_a)
{
	vi2_t a = rotate(_a);
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

#define _bs2_DP_Tab_desc "Dynamic Programming tabulation"

/* TC : O(n^2)
 * SC : O(n^2)
 */
namespace DP_Tab
{
int maxHeight(vi2_t &_a)
{
	vi2_t a = rotate(_a);
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

#define _bs2_DP_Tab2_desc "Dynamic Programming tabulation space optimized"

/* TC : O(n^2)
 * SC : O(n)
 */
namespace DP_Tab2
{
int maxHeight(vi2_t &_a)
{
	vi2_t a = rotate(_a);
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

#define _bs2_DP_Tab3_desc "Dynamic Programming tabulation simple"

/* TC : O(n^2)
 * SC : O(n)
 */
namespace DP_Tab3
{
int maxHeight(vi2_t &_a)
{
	vi2_t a = rotate(_a);
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
#define _bs2_desc_prefix "Box stacking 02"

#define _BS2_NAME(var) var
#define _BS2_DESC(var) _bs2_desc_prefix " - " _bs2_##var##_desc

#define _BS2_TEST(var)                                                       \
	TEST(_BS2_NAME(var), _BS2_DESC(var))                                 \
	{                                                                    \
		using namespace _BS2_NAME(var);                              \
		int e, a;                                                    \
		vi2_t i, t;                                                  \
		i = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};         \
		t = i;                                                       \
		e = 60;                                                      \
		a = maxHeight(t);                                            \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

_BS2_TEST(Recursive);
_BS2_TEST(DP_Tab);
_BS2_TEST(DP_Tab2);
_BS2_TEST(DP_Tab3);

INIT_TEST_MAIN();
