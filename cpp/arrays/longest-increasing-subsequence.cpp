/**
 * 300. Longest Increasing Subsequence
 * ===================================
 *
 * Solution taken from:
 * https://leetcode.com/problems/longest-increasing-subsequence/solutions/1326308/c-python-dp-binary-search-bit-segment-tree-solutions-picture-explain-o-nlogn
 */

#include <bits/stdc++.h>

using namespace std;

class _01_recursive;

/* TC : O(n^2)
 * SC : O(n)
 */
class _02_dp_tab
{
public:
	int lengthOfLIS(vector<int> &nums)
	{
		int n = nums.size(), ans = 1;
		vector<int> dp(n, 1);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < i; ++j)
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1);
					ans = max(ans, dp[i]);
				}
		return ans;
	}

	int operator()(vector<int> &nums) { return this->lengthOfLIS(nums); }
};

/* TC : O(n log n)
 * SC : O(n)
 */
class _03_greedy_with_binary_search
{
public:
	int lengthOfLIS(vector<int> &nums)
	{
		vector<int> sub;
		for (int x : nums) {
			if (sub.empty() || sub[sub.size() - 1] < x) {
				sub.push_back(x);
			} else {
				// Find the index of the first element >= x
				auto it =
				    lower_bound(sub.begin(), sub.end(), x);
				*it = x; // Replace that number with x
			}
		}
		return sub.size();
	}

	int operator()(vector<int> &nums) { return this->lengthOfLIS(nums); }
};

class _03_01_greedy_with_binary_search_seq
{
public:
	vector<int> pathOfLIS(vector<int> &nums)
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

	vector<int> operator()(vector<int> &nums)
	{
		return this->pathOfLIS(nums);
	}
};

class _04_binary_indexed_tree;
class _05_binary_indexed_tree_compress;
class _06_segment_tree;

typedef std::function<int(vector<int> &)> func_t;

void test_impl(vector<vector<int>> ip, vector<int> op, func_t impl)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = impl(ip[i]);
		if (op[i] != t) {
			cerr << "test failed: expected " << op[i]
			     << ", actual " << t << endl;
			exit(1);
		}
		cout << t << endl;
	}
}

int main(int, char **)
{
	vector<vector<int>> ip{
	    {10, 9, 2, 5, 3, 7, 101, 18},
	    {0, 1, 0, 3, 2, 3},
	    {7, 7, 7, 7, 7, 7, 7},
	};
	vector<int> op{4, 4, 1};

	vector<func_t> impls{
	    _02_dp_tab(),
	    _03_greedy_with_binary_search(),
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
