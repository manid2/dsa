/**
 * 887. Super Egg Drop
 * ===================
 *
 * Solution taken from:
 * https://leetcode.com/problems/super-egg-drop/solutions/792736/cpp-explained-recursive-memoization-optimization-dp-well-explained-easy-to-understand
 */

#include <bits/stdc++.h>

using namespace std;

/* TC : O(n * (2^min(n,k))
 * SC : O(1) ignore recursive function calls stack
 */
class _01_recursive
{
public:
	int superEggDrop(int k, int n) { return find(k, n); }

	int find(int k, int n)
	{
		if (n == 0 || n == 1) return n;
		if (k == 1) return n;
		int ans = INT_MAX;
		for (int i = 1; i <= n; i++) {
			int temp =
			    1 + max(find(k - 1, i - 1), find(k, n - i));
			ans = min(ans, temp);
		}
		return ans;
	}

	int operator()(int k, int n) { return this->superEggDrop(k, n); }
};

class _02_dp_memo; // TODO Implement

/* TC : O((n * k) * log n)
 * SC : O(n *k)
 */
class _03_dp_memo_binary_search
{
public:
	int superEggDrop(int k, int n)
	{
		vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1));
		return find(k, n, dp);
	}

	int find(int k, int n, vector<vector<int>> &dp)
	{
		if (n == 0 || n == 1) return n;
		if (k == 1) return n;
		if (dp[k][n] != -1) return dp[k][n];

		int ans = INT_MAX, l = 1, h = n, temp = 0;
		while (l <= h) {
			int mid = (l + h) / 2;
			int left = find(k - 1, mid - 1, dp);
			int right = find(k, n - mid, dp);
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

	int operator()(int k, int n) { return this->superEggDrop(k, n); }
};

/**
 * Solution taken from:
 * https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/
 *
 * TC : O(N * K)
 * SC : O(N * K)
 */
class _04_dp_tab
{
public:
	int superEggDrop(int k, int n)
	{
		vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
		int m = 0;
		while (dp[m][k] < n) {
			m++;
			for (int i = 1; i <= k; i++) {
				dp[m][i] =
				    1 + dp[m - 1][i - 1] + dp[m - 1][i];
			}
		}
		return m;
	}

	int operator()(int k, int n) { return this->superEggDrop(k, n); }
};

/**
 * TC : O(N * log K)
 * SC : O(N)
 */
class _05_dp_tab_optimized
{
public:
	int superEggDrop(int k, int n)
	{
		vector<int> dp(k + 1, 0);
		int m = 0;
		for (; dp[k] < n; m++) {
			for (int i = k; i > 0; i--) {
				dp[i] += 1 + dp[i - 1];
			}
		}
		return m;
	}

	int operator()(int k, int n) { return this->superEggDrop(k, n); }
};

typedef std::function<int(int, int)> func_t;

void test_impl(vector<std::pair<int, int>> ip, vector<int> op, func_t impl)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = impl(ip[i].first, ip[i].second);
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
	vector<std::pair<int, int>> ip{
	    std::make_pair(1, 2),
	    std::make_pair(2, 6),
	    std::make_pair(3, 14),
	    std::make_pair(2, 3),
	};
	vector<int> op{2, 3, 4, 2};

	vector<func_t> impls{
	    _01_recursive(), _03_dp_memo_binary_search(),
	    /* FIXME segmentation fault
	    _04_dp_tab(),
	    _05_dp_tab_optimized(),
	    */
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
