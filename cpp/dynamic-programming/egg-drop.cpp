/**
 * 887. Super Egg Drop
 * ===================
 *
 * Solution taken from:
 * https://leetcode.com/problems/super-egg-drop/solutions/792736/cpp-explained-recursive-memoization-optimization-dp-well-explained-easy-to-understand
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

	virtual int superEggDrop(int eggs, int floors) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n * 2^n)
 * SC : O(1) ignore recursive function calls stack
 */
class _01_recursive : public _00_test
{
public:
	_01_recursive() : _00_test("Egg drop puzzle recursive") {}

	int superEggDrop(int k, int n) override { return find(k, n); }

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
};

class _02_dp_memo;

/* TC : O((n * k) * log n)
 * SC : O(n *k)
 */
class _03_dp_memo_binary_search : public _00_test
{
public:
	_03_dp_memo_binary_search()
	    : _00_test("Egg drop puzzle dynamic programming tabulation "
	               "binary search")
	{
	}

	int superEggDrop(int k, int n) override
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
};

/**
 * Solution taken from:
 * https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/
 *
 * TC : O(n * k)
 * SC : O(n * k)
 */
class _04_dp_tab : public _00_test
{
public:
	_04_dp_tab()
	    : _00_test("Egg drop puzzle dynamic programming tabulation")
	{
	}

	int superEggDrop(int k, int n) override
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
};

/**
 * TC : O(n * log k)
 * SC : O(n)
 */
class _05_dp_tab_space_optimized : public _00_test
{
public:
	_05_dp_tab_space_optimized()
	    : _00_test("Egg drop puzzle dynamic programming tabulation space "
	               "optimized")
	{
	}

	int superEggDrop(int k, int n) override
	{
		vector<int> dp(k + 1, 0);
		int m = 0;
		for (; dp[k] < n; m++)
			for (int i = k; i > 0; i--) dp[i] += 1 + dp[i - 1];
		return m;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
void test_impl(const vector<std::pair<int, int>> ip, const vector<int> op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->superEggDrop(ip[i].first, ip[i].second);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: eggs = " << ip[i].first
			     << ", floors = " << ip[i].second
			     << "  output: min = " << t << "\n";
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

	/* FIXME segmentation fault
	   _04_dp_tab(),
	   _05_dp_tab_space_optimized(),
	   */

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_recursive>(),
	    make_shared<_03_dp_memo_binary_search>(),
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
