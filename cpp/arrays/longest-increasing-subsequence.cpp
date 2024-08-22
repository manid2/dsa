/**
 * Longest Increasing Subsequence
 * ==============================
 *
 * Refer:
 *
 * https://leetcode.com/problems/longest-increasing-subsequence/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _lis_DP_Tab_desc "Dynamic Programming tabulation"

/* TC : O(n^2)
 * SC : O(n)
 */
namespace DP_Tab
{
int lengthOfLIS(const vi_t &a)
{
	int n = size(a), r = 1;
	vi_v(dp, n, 1);
	fii (i, n)
		fii (j, i)
			if (a[i] > a[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
				r = max(r, dp[i]);
			}
	return r;
}
} // namespace DP_Tab

#define _lis_Greedy_desc "Greedy with Binary Search"

/* TC : O(n log n)
 * SC : O(n)
 */
namespace Greedy
{
int lengthOfLIS(const vi_t &a)
{
	vi_t s;
	for (int x : a) {
		if (s.empty() || s[s.size() - 1] < x) {
			s.push_back(x);
		} else {
			// Find the index of the first element >= x
			auto it = lower_bound(begin(s), end(s), x);
			*it = x; // Replace that number with x
		}
	}
	return size(s);
}
} // namespace Greedy

// Finds the sequence instead of length
class _04_01_greedy_with_binary_search_seq
{
public:
	vector<int> pathOfLIS(const vector<int> &nums)
	{
		int n = nums.size();
		vector<int> sub, subIndex;
		vector<int> trace(n, -1);

		for (int i = 0; i < n; ++i) {
			if (sub.empty() || sub[sub.size() - 1] < nums[i]) {
				if (!sub.empty())
					trace[i] = subIndex[sub.size() - 1];
				sub.push_back(nums[i]);
				subIndex.push_back(i);
			} else {
				int idx = lower_bound(sub.begin(), sub.end(),
				                      nums[i]) -
				          sub.begin();
				if (idx > 0) trace[i] = subIndex[idx - 1];
				sub[idx] = nums[i];
				subIndex[idx] = i;
			}
		}
		vector<int> path;
		int t = subIndex[subIndex.size() - 1];
		while (t != -1) {
			path.push_back(nums[t]);
			t = trace[t];
		}
		reverse(path.begin(), path.end());
		return path;
	}
};

class _05_binary_indexed_tree;
class _06_binary_indexed_tree_compress;
class _07_segment_tree;

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _lis_check(i, e)                                                     \
	{                                                                    \
		vi_t t = i;                                                  \
		int a = lengthOfLIS(t);                                      \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _lis_desc_prefix "Longest Increasing Subsequence"

#define _LIS_NAME(var) var
#define _LIS_DESC(var) _lis_desc_prefix " - " _lis_##var##_desc

#define _LIS_TEST(var)                                                       \
	TEST(_LIS_NAME(var), _LIS_DESC(var))                                 \
	{                                                                    \
		using namespace _LIS_NAME(var);                              \
		vi2_t ip{                                                    \
		    {10, 9, 2, 5, 3, 7, 101, 18},                            \
		    {0, 1, 0, 3, 2, 3},                                      \
		    {7, 7, 7, 7, 7, 7, 7},                                   \
		};                                                           \
		vi_t op{4, 4, 1};                                            \
		int n = size(ip);                                            \
		fii (i, n) _lis_check(ip[i], op[i]);                         \
	}

_LIS_TEST(DP_Tab);
_LIS_TEST(Greedy);

INIT_TEST_MAIN();
