/**
 * 1691. Maximum Height by Stacking Cuboids
 * =========================================
 *
 * Solution taken from:
 *
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/solutions/4204904/logic-behind-sorting-and-dp-for-interviews-clean-c-code-recursion-to-dp-space-optimised
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/solutions/2544040/c-recursion-memoization-tabulation-spaceoptimization
 */

#include <bits/stdc++.h>

using namespace std;

/* TC : O(n log n x 2^n)
 * SC : O(n)
 */
class _01_recursive
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		return solve(cuboids, -1, 0);
	}

	int solve(vector<vector<int>> &cuboids, int prev, int curr)
	{
		if (curr == static_cast<int>(cuboids.size())) return 0;
		int pick = INT_MIN;
		if (prev == -1 || (cuboids[prev][0] <= cuboids[curr][0] &&
		                   cuboids[prev][1] <= cuboids[curr][1] &&
		                   cuboids[prev][2] <= cuboids[curr][2])) {
			pick =
			    cuboids[curr][2] + solve(cuboids, curr, curr + 1);
		}
		int skip = solve(cuboids, prev, curr + 1);
		return max(pick, skip);
	}

	int operator()(vector<vector<int>> &cuboids)
	{
		return this->maxHeight(cuboids);
	}
};

class _02_dp_memo;

/* TC O(n^2)
 * SC O(n^2)
 */
class _03_dp_tab
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		int n = cuboids.size();
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		for (int i = n - 1; i >= 0; i--) {
			for (int j = n - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 ||
				    (cuboids[j][0] <= cuboids[i][0] &&
				     cuboids[j][1] <= cuboids[i][1] &&
				     cuboids[j][2] <= cuboids[i][2])) {
					pick =
					    cuboids[i][2] + dp[i + 1][i + 1];
				}
				int skip = dp[i + 1][j + 1];
				dp[i][j + 1] = max(pick, skip);
			}
		}
		return dp[0][0];
	}

	int operator()(vector<vector<int>> &cuboids)
	{
		return this->maxHeight(cuboids);
	}
};

/* TC O(n^2)
 * SC O(n)
 */
class _04_dp_tab_space_optimized
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		int n = cuboids.size();
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		vector<int> last(n + 1, 0), curr(n + 1, 0);
		for (int i = n - 1; i >= 0; i--) {
			for (int j = n - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 ||
				    (cuboids[j][0] <= cuboids[i][0] &&
				     cuboids[j][1] <= cuboids[i][1] &&
				     cuboids[j][2] <= cuboids[i][2])) {
					pick = cuboids[i][2] + last[i + 1];
				}
				int skip = last[j + 1];
				curr[j + 1] = max(pick, skip);
			}
			last = curr;
		}
		return last[0];
	}

	int operator()(vector<vector<int>> &cuboids)
	{
		return this->maxHeight(cuboids);
	}
};

/**
 * Solution taken from:
 *
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/solutions/970293/java-c-python-dp-prove-with-explanation
 */
class _05_dp_tab_simple
{
public:
	int maxHeight(vector<vector<int>> &A)
	{
		for (auto &a : A) sort(begin(a), end(a));
		A.push_back({0, 0, 0});
		sort(begin(A), end(A));
		int n = A.size(), res = 0;
		vector<int> dp(n);
		for (int i = 1; i < n; i++)
			for (int j = 0; j < i; j++)
				if (A[j][0] <= A[i][0] &&
				    A[j][1] <= A[i][1] &&
				    A[j][2] <= A[i][2]) {
					dp[i] = max(dp[i], dp[j] + A[i][2]);
					res = max(res, dp[i]);
				}
		return res;
	}

	int operator()(vector<vector<int>> &cuboids)
	{
		return this->maxHeight(cuboids);
	}
};

using cuboids_t = std::vector<std::vector<int>>;
typedef std::function<int(cuboids_t &)> func_t;

void test_impl(vector<cuboids_t> ip, vector<int> op, func_t impl)
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
	vector<cuboids_t> ip{
	    {{50, 45, 20}, {95, 37, 53}, {45, 23, 12}},
	    {{38, 25, 45}, {76, 35, 3}},
	    {{7, 11, 17},
	     {7, 17, 11},
	     {11, 7, 17},
	     {11, 17, 7},
	     {17, 7, 11},
	     {17, 11, 7}},
	};
	vector<int> op{190, 76, 102};

	vector<func_t> impls{
	    _01_recursive(),
	    _03_dp_tab(),
	    _04_dp_tab_space_optimized(),
	    _05_dp_tab_simple(),
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
