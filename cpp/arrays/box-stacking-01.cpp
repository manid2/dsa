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
		return (prev[0] <= curr[0] && prev[1] <= curr[1] &&
		        prev[2] <= curr[2]);
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
	_01_recursive() : _00_test("Box stacking 01 recursive") {}

	int maxHeight(vector<vector<int>> &cuboids) override
	{
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		return solve(cuboids, -1, 0);
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

class _02_dp_memo;

/* TC : O(n^2)
 * SC : O(n^2)
 */
class _03_dp_tab : public _00_test
{
public:
	_03_dp_tab()
	    : _00_test("Box stacking 01 dynamic programming tabulation")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
	{
		int n = cuboids.size();
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		for (int i = n - 1; i >= 0; i--) {
			for (int j = n - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 ||
				    check(cuboids[j], cuboids[i])) {
					pick =
					    cuboids[i][2] + dp[i + 1][i + 1];
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
	    : _00_test("Box stacking 01 dynamic programming tabulation space "
	               "optimized")
	{
	}

	int maxHeight(vector<vector<int>> &cuboids) override
	{
		int n = cuboids.size();
		for (auto &c : cuboids) sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		vector<int> last(n + 1, 0), curr(n + 1, 0);
		for (int i = n - 1; i >= 0; i--) {
			for (int j = n - 1; j >= -1; j--) {
				int pick = INT_MIN;
				if (j == -1 ||
				    check(cuboids[j], cuboids[i])) {
					pick = cuboids[i][2] + last[i + 1];
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

/* TC : O(n^2)
 * SC : O(n)
 */
class _05_dp_tab_simple : public _00_test
{
public:
	_05_dp_tab_simple()
	    : _00_test("Box stacking 01 dynamic programming tabulation "
	               "simple")
	{
	}

	int maxHeight(vector<vector<int>> &A) override
	{
		for (auto &a : A) sort(begin(a), end(a));
		A.push_back({0, 0, 0});
		sort(begin(A), end(A));
		int n = A.size(), res = 0;
		vector<int> dp(n);
		for (int i = 1; i < n; i++)
			for (int j = 0; j < i; j++)
				if (check(A[j], A[i])) {
					dp[i] = max(dp[i], dp[j] + A[i][2]);
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
