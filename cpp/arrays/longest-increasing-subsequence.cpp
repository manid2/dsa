/**
 * 300. Longest Increasing Subsequence
 * ===================================
 *
 * Solution taken from:
 * https://leetcode.com/problems/longest-increasing-subsequence/solutions/1326308/c-python-dp-binary-search-bit-segment-tree-solutions-picture-explain-o-nlogn
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual int lengthOfLIS(const vector<int> &nums) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

class _01_recursive;
class _02_dp_memo;

/* TC : O(n^2)
 * SC : O(n)
 */
class _03_dp_tab : public _00_test
{
public:
	_03_dp_tab()
	    : _00_test("Longest Increasing Sequence dynamic programming "
	               "tabulation")
	{
	}

	int lengthOfLIS(const vector<int> &nums) override
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
};

/* TC : O(n log n)
 * SC : O(n)
 */
class _04_greedy_with_binary_search : public _00_test
{
public:
	_04_greedy_with_binary_search()
	    : _00_test("Longest Increasing Sequence greedy with binary "
	               "search")
	{
	}

	int lengthOfLIS(const vector<int> &nums) override
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
};

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
string _vec2str(vector<int> &vec)
{
	ostringstream oss;
	oss << "{";
	copy(vec.begin(), vec.end() - 1, ostream_iterator<int>(oss, ", "));
	oss << vec.back();
	oss << "}";
	return oss.str();
}

void test_impl(vector<vector<int>> &ip, vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->lengthOfLIS(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: nums = " << _vec2str(ip[i])
			     << "  output: maxLen = " << t << "\n";
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

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_03_dp_tab>(),
	    make_shared<_04_greedy_with_binary_search>(),
	};

	for (size_t i = 0; i < impls.size(); i++) {
		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "Testing implementation " << i + 1 << " "
			     << impls[i]->getName() << "\n";

		test_impl(ip, op, impls[i]);
	}

	cout << "Executed " << impls.size() << " implementations"
	     << " with " << ip.size() << " tests." << endl;
	return 0;
}
