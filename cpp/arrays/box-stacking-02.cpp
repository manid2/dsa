/**
 * Box stacking maximum height - 02
 * ================================
 *
 * This is a variation of:
 *
 * LC-1691: Maximum Height by Stacking Cuboids
 *
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/description/
 *
 * Solutions taken from:
 *
 * https://leetcode.com/discuss/interview-question/3551334/Box-Stacking
 * https://www.geeksforgeeks.org/box-stacking-problem-dp-22/
 */

#include <bits/stdc++.h>

using namespace std;

class _00_base
{
public:
	bool check(const vector<int>& prev, const vector<int>& curr)
	{
		return (prev[0] < curr[0] && prev[1] < curr[1]);
	}

	vector<vector<int>> rotateCubiods(const vector<vector<int>> &cuboids)
	{
		int n = cuboids.size();
		vector<vector<int>> cr;
		for (int i = 0; i < n; i++) {
			int w = cuboids[i][0];
			int l = cuboids[i][1];
			int h = cuboids[i][2];
			cr.push_back({w, l, h});
			cr.push_back({w, h, l});
			cr.push_back({l, h, w});
			cr.push_back({l, w, h});
			cr.push_back({h, w, l});
			cr.push_back({h, l, w});
		}
		return cr;
	}
};

/* TC : O(n log n x 2^n)
 * SC : O(n)
 */
class _01_recursive : public _00_base
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		sort(cr.begin(), cr.end());
		return solve(cr, -1, 0);
	}

	int solve(vector<vector<int>> &cuboids, int prev, int curr)
	{
		if (curr == cuboids.size()) return 0;
		int pick = INT_MIN;
		if (prev == -1 || check(cuboids[prev], cuboids[curr])) {
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

class _02_dp_memo : public _00_base
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		sort(cr.begin(), cr.end());
		vector<vector<int>> dp(cr.size(),
		                       vector<int>(cr.size() + 1, -1));
		return solve(cr, -1, 0, dp);
	}

	int solve(vector<vector<int>> &cuboids, int prev, int curr,
	          vector<vector<int>> &dp)
	{
		if (curr == cuboids.size()) return 0;
		if (dp[curr][prev + 1] != -1) return dp[curr][prev + 1];
		int pick = INT_MIN;
		if (prev == -1 || check(cuboids[prev], cuboids[curr])) {
			pick = cuboids[curr][2] +
			       solve(cuboids, curr, curr + 1, dp);
		}
		int skip = solve(cuboids, prev, curr + 1, dp);
		return dp[curr][prev + 1] = max(pick, skip);
	}

	int operator()(vector<vector<int>> &cuboids)
	{
		return this->maxHeight(cuboids);
	}
};

/* TC O(n^2)
 * SC O(n^2)
 */
class _03_dp_tab : public _00_base
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		sort(cr.begin(), cr.end());
		vector<vector<int>> dp(cr.size() + 1,
		                       vector<int>(cr.size() + 1, 0));
		for (int i = cr.size() - 1; i >= 0; i--) {
			for (int j = i - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 || check(cr[j], cr[i])) {
					pick = cr[i][2] + dp[i + 1][i + 1];
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
class _04_dp_tab_space_optimized : public _00_base
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		sort(cr.begin(), cr.end());
		vector<int> last(cr.size() + 1, 0), curr(cr.size() + 1, 0);
		for (int i = cr.size() - 1; i >= 0; i--) {
			for (int j = i - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 || check(cr[j], cr[i])) {
					pick = cr[i][2] + last[i + 1];
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
class _05_dp_tab_simple : public _00_base
{
public:
	int maxHeight(vector<vector<int>> &cuboids)
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		cr.push_back({0, 0, 0});
		sort(cr.begin(), cr.end());
		int n = cr.size(), res = 0;
		vector<int> dp(n);
		for (int i = 1; i < n; i++)
			for (int j = 0; j < i; j++)
				if (check(cr[j], cr[i])) {
					dp[i] = max(dp[i], dp[j] + cr[i][2]);
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

int main(int argc, char *argv[])
{
	vector<cuboids_t> ip{
	    {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}},
	};
	vector<int> op{60};

	vector<func_t> impls{
	    _01_recursive(),
	    _02_dp_memo(),
	    _03_dp_tab(),
	    _04_dp_tab_space_optimized(),
	    _05_dp_tab_simple(),
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
