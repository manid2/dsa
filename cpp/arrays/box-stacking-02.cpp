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

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual int maxHeight(vector<vector<int>> &cuboids) = 0;

	bool check(const vector<int> &prev, const vector<int> &curr)
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

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n log n + 2^n)
 * SC : O(n)
 */
class _01_recursive : public _00_test
{
public:
	_01_recursive() : _00_test("Box stacking 02 recursive") {}

	int maxHeight(vector<vector<int>> &cuboids) override
	{
		vector<vector<int>> cr = this->rotateCubiods(cuboids);
		sort(cr.begin(), cr.end());
		return solve(cr, -1, 0);
	}

	int solve(vector<vector<int>> &cuboids, int prev, int curr)
	{
		if (curr == static_cast<int>(cuboids.size())) return 0;
		int pick = INT_MIN;
		if (prev == -1 || check(cuboids[prev], cuboids[curr])) {
			pick =
			    cuboids[curr][2] + solve(cuboids, curr, curr + 1);
		}
		int skip = solve(cuboids, prev, curr + 1);
		return max(pick, skip);
	}
};

/* TC : O(n log n + n^2)
 * SC : O(n^2)
 */
class _02_dp_memo : public _00_test
{
public:
	_02_dp_memo()
	    : _00_test("Box stacking 02 dynamic problems memoization")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
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
		if (curr == static_cast<int>(cuboids.size())) return 0;
		if (dp[curr][prev + 1] != -1) return dp[curr][prev + 1];
		int pick = INT_MIN;
		if (prev == -1 || check(cuboids[prev], cuboids[curr])) {
			pick = cuboids[curr][2] +
			       solve(cuboids, curr, curr + 1, dp);
		}
		int skip = solve(cuboids, prev, curr + 1, dp);
		return dp[curr][prev + 1] = max(pick, skip);
	}
};

/* TC : O(n log n + n^2)
 * SC : O(n^2)
 */
class _03_dp_tab : public _00_test
{
public:
	_03_dp_tab() : _00_test("Box stacking 02 dynamic problems tabulation")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
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
};

/* TC : O(n^2)
 * SC : O(n)
 */
class _04_dp_tab_space_optimized : public _00_test
{
public:
	_04_dp_tab_space_optimized()
	    : _00_test("Box stacking 02 dynamic programming tabulation space "
	               "optimized")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
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
};

/**
 * Solution taken from:
 *
 * https://leetcode.com/problems/maximum-height-by-stacking-cuboids/solutions/970293/java-c-python-dp-prove-with-explanation
 */

/* TC O(n^2)
 * SC O(n)
 */
class _05_dp_tab_simple : public _00_test
{
public:
	_05_dp_tab_simple()
	    : _00_test("Box stacking 02 dynamic programming tabulation "
	               "simple")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
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
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
using vec2_t = vector<vector<int>>;

string _vec2str(const vector<int> &vec)
{
	ostringstream oss;
	oss << "{";
	copy(vec.begin(), vec.end() - 1, ostream_iterator<int>(oss, ", "));
	oss << vec.back();
	oss << "}";
	return oss.str();
}

string _2vec2str(const vec2_t &vec2)
{
	ostringstream oss;
	oss << "{";
	for (int i = 0; auto &v : vec2) {
		if (i++) oss << ", ";
		oss << _vec2str(v);
	}
	oss << "}";
	return oss.str();
}

void test_impl(vector<vec2_t> &ip, const vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->maxHeight(ip[i]);
		if (op[i] != t) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: cuboids = " << _2vec2str(ip[i])
			     << "  output: maxHeight = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<vec2_t> ip{
	    {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}},
	};

	vector<int> op{60};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_recursive>(),
	    make_shared<_03_dp_tab>(),
	    make_shared<_04_dp_tab_space_optimized>(),
	    make_shared<_05_dp_tab_simple>(),
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
