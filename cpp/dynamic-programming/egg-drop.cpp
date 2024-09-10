/**
 * Super Egg Drop
 * ==============
 *
 * Refer:
 *
 * https://leetcode.com/problems/super-egg-drop/
 * https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/
 * https://medium.com/@parv51199/egg-drop-problem-using-dynamic-programming-e22f67a1a7c3
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _ed_Recursive_desc "Recursive"

/* TC : O(n * 2^n)
 * SC : O(1) ignore recursive function calls stack
 */
namespace Recursive
{
int solve(int k, int n)
{
	if (n == 0 || n == 1) return n;
	if (k == 1) return n;
	int ans = INT_MAX;
	for (int i = 1; i <= n; i++) {
		int temp = 1 + max(solve(k - 1, i - 1), solve(k, n - i));
		ans = min(ans, temp);
	}
	return ans;
}

int superEggDrop(int k, int n) { return solve(k, n); }
}; // namespace Recursive

#define _ed_DP_Memo_desc "Dynamic Programming Memoization with Binary Search"

/* TC : O((n * k) * log n)
 * SC : O(n *k)
 */
namespace DP_Memo
{
int solve(int k, int n, vector<vector<int>> &dp)
{
	if (n == 0 || n == 1) return n;
	if (k == 1) return n;
	if (dp[k][n] != -1) return dp[k][n];

	int ans = INT_MAX, l = 1, h = n, temp = 0;
	while (l <= h) {
		int mid = (l + h) / 2;
		int left = solve(k - 1, mid - 1, dp);
		int right = solve(k, n - mid, dp);
		temp = 1 + max(left, right);
		if (left < right) {
			l = mid + 1;
		} else {
			h = mid - 1;
		}
		ans = min(ans, temp);
	}
	return dp[k][n] = ans;
}

int superEggDrop(int k, int n)
{
	vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1));
	return solve(k, n, dp);
}
}; // namespace DP_Memo

#define _ed_DP_Tab_desc "Dynamic Programming Tabulation O(n^3)"

/**
 * TC : O(n * k^2) => O(n^3)
 * SC : O(n * k)   => O(n^2)
 */
namespace DP_Tab
{
int superEggDrop(int k, int n)
{
	vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

	// For k eggs & 1 floor only 1 trail is required
	for (int i = 1; i <= k; i++) dp[i][1] = 1;

	// For 1 egg & n floors i'th trails are required
	for (int i = 1; i <= n; i++) dp[1][i] = i;

	for (int i = 2; i <= k; i++) {
		for (int j = 2; j <= n; j++) {
			dp[i][j] = INT_MAX;
			// Find the min of max trails at each floor
			for (int x = 1; x <= j; x++) {
				int m =
				    1 + max(dp[i - 1][x - 1], dp[i][j - x]);
				dp[i][j] = min(dp[i][j], m);
			}
		}
	}
	return dp[k][n];
}
}; // namespace DP_Tab

#define _ed_DP_Tab2_desc "Dynamic Programming Tabulation 2 O(n^2)"

/**
 * TC : O(n * k)
 * SC : O(n * k)
 */
namespace DP_Tab2
{
int superEggDrop(int k, int n)
{
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	int m = 0; // Number of moves
	while (dp[m][k] < n) {
		m++;
		for (int i = 1; i <= k; i++) {
			dp[m][i] = 1 + dp[m - 1][i - 1] + dp[m - 1][i];
		}
	}
	return m;
}
}; // namespace DP_Tab2

#define _ed_DP_Tab3_desc "Dynamic Programming Tabulation 3 SC O(n)"

/**
 * TC : O(n * k)
 * SC : O(n)
 */
namespace DP_Tab3
{
int superEggDrop(int k, int n)
{
	vector<int> dp(k + 1, 0);
	int m = 0;
	for (; dp[k] < n; m++)
		for (int i = k; i > 0; i--) dp[i] += 1 + dp[i - 1];
	return m;
}
}; // namespace DP_Tab3

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _ed_check(k, n, e, _ns)                                              \
	{                                                                    \
		using namespace _ns;                                         \
		int a = superEggDrop(k, n);                                  \
		string im = format("Eggs {}, Floors {}", k, n);              \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(im, a);                                          \
	}

#define _ed_desc_prefix "Box stacking 01"

#define _ED_NAME(var) var
#define _ED_DESC(var) _ed_desc_prefix " - " _ed_##var##_desc

#define _ED_TEST(var)                                                        \
	TEST(_ED_NAME(var), _ED_DESC(var))                                   \
	{                                                                    \
		vi_t _k{1, 2, 3, 2};                                         \
		vi_t _n{2, 6, 14, 3};                                        \
		vi_t _e{2, 3, 4, 2};                                         \
		int n = size(_e);                                            \
		fii (i, n) _ed_check(_k[i], _n[i], _e[i], _ED_NAME(var));    \
	}

_ED_TEST(Recursive);
_ED_TEST(DP_Tab);
_ED_TEST(DP_Tab2);
_ED_TEST(DP_Tab3);

INIT_TEST_MAIN();
