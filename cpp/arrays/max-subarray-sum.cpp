/**
 * Largest contiguous sub-array sum (Kadane's algorithm)
 * =====================================================
 *
 * Leetcode: [53. Maximum Subarray][lc53]
 *
 * Given an integer array nums, find the subarray with the largest sum, and
 * return its sum.
 *
 * Tags: #strings, #medium
 *
 * Example 1:
 *
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 *
 * Example 2:
 *
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 *
 * Example 3:
 *
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *
 * Constraints:
 *
 * 1 <= nums.length <= 105
 * -104 <= nums[i] <= 104
 *
 * Follow up: If you have figured out the O(n) solution, try coding another
 * solution using the divide and conquer approach, which is more subtle.
 *
 * Solution
 * --------
 *
 * [archit91's solution][lcdi1]
 * [bealdung.com Java solution][bd1]
 *
 * [lc53]: https://leetcode.com/problems/maximum-subarray/
 * [lcdi1]: https://leetcode.com/problems/maximum-subarray/solutions/1595195/c-python-7-simple-solutions-w-explanation-brute-force-dp-kadane-divide-conquer
 * [bd1]: https://www.baeldung.com/java-maximum-subarray
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

	virtual int maxSubArray(const vector<int> &nums) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/**
 * TC : O(n^2) => For trying all possible n*(n+1)/2 sub arrays
 * SC : O(1)
 */
class _01_brute_force : public _00_test
{
public:
	_01_brute_force() : _00_test("Maximum subarray sum brute force") {}

	int maxSubArray(const vector<int> &nums) override
	{
		int n = nums.size(), sum = INT_MIN, b = 0, e = 0;
		for (int i = 0; i < n; i++) {
			int curr_sum = 0;
			for (int j = i; j < n; j++) {
				curr_sum += nums[j];
				if (curr_sum > sum) {
					sum = curr_sum;
					b = i;
					e = j;
				}
			}
		}
		int t = 0;
		for (int i = b; i <= e; i++) t += nums[i];
		return t == sum ? sum : INT_MIN;
	}
};

/**
 * TC : O(n^2) => For trying all possible n*(n+1)/2 sub arrays
 * SC : O(n)   => For recursion
 */
class _02_recursive : public _00_test
{
public:
	_02_recursive() : _00_test("Maximum subarray sum recursive") {}

	int maxSubArray(const vector<int> &nums) override
	{
		return solve(nums, 0, false);
	}

	int solve(const vector<int> &A, int i, bool mustPick)
	{
		if (i >= static_cast<int>(A.size()))
			return mustPick ? 0 : INT_MIN;
		if (mustPick) return max(0, A[i] + solve(A, i + 1, true));
		return max(solve(A, i + 1, false),
		           A[i] + solve(A, i + 1, true));
	}
};

/**
 * TC : O(n) => For calculating 2n states and reusing memos
 * SC : O(n) => For recursion
 */
class _03_dp_memo : public _00_test
{
public:
	_03_dp_memo()
	    : _00_test("Maximum subarray sum dynamic programming memoization")
	{
	}

	int maxSubArray(const vector<int> &nums) override
	{
		vector<vector<int>> dp(2, vector<int>(size(nums), -1));
		return solve(nums, 0, false, dp);
	}

	int solve(const vector<int> &A, int i, bool mustPick,
	          vector<vector<int>> &dp)
	{
		if (i >= static_cast<int>(A.size()))
			return mustPick ? 0 : INT_MIN;
		if (dp[mustPick][i] != -1) return dp[mustPick][i];
		if (mustPick)
			return dp[mustPick][i] =
			           max(0, A[i] + solve(A, i + 1, true, dp));
		return dp[mustPick][i] =
		           max(solve(A, i + 1, false, dp),
		               A[i] + solve(A, i + 1, true, dp));
	}
};

/**
 * TC : O(n)
 * SC : O(n) => For dp table
 */
class _04_dp_tab : public _00_test
{
public:
	_04_dp_tab()
	    : _00_test("Maximum subarray sum dynamic programming tabulation")
	{
	}

	int maxSubArray(const vector<int> &nums) override
	{
		// dp[i] is the maximum subarray sum ending at i
		vector<int> dp(nums);
		for (int i = 1; i < static_cast<int>(nums.size()); i++)
			dp[i] = max(nums[i], nums[i] + dp[i - 1]);
		// maximum of all max subarray sums ending at i.
		return *max_element(begin(dp), end(dp));
	}
};

/**
 * TC : O(n)
 * SC : O(1)
 */
class _05_kadanes : public _00_test
{
public:
	_05_kadanes() : _00_test("Maximum subarray sum Kadane's algorithm") {}

	int maxSubArray(const vector<int> &nums) override
	{
		int curr_sum = 0, sum = INT_MIN, b = 0, e = 0, _s = 0;
		for (int i = 0; i < static_cast<int>(nums.size()); i++) {
			curr_sum += nums[i];
			if (curr_sum > sum) {
				sum = curr_sum;
				b = _s;
				e = i;
			}

			if (curr_sum < 0) {
				curr_sum = 0;
				_s = i + 1;
			}
		}
		int t = 0;
		for (int i = b; i <= e; i++) t += nums[i];
		return t == sum ? sum : INT_MIN;
	}
};

/**
 * TC : O(n log n)
 * SC : O(log n)
 *
 * Recurrence relation for this method T(n) = 2T(n/2) + O(n) as:
 *
 * - Recurring for left and right half (2T(n/2)).
 * - Calculating maximum subarray sum O(n).
 *
 * Solving this recurrence using master theorem to get TC O(n log n)
 */
class _06_divide_conquer : public _00_test
{
public:
	_06_divide_conquer()
	    : _00_test("Maximum subarray sum divided & conquer")
	{
	}

	int maxSubArray(const vector<int> &nums) override
	{
		return solve(nums, 0, size(nums) - 1);
	}

	int solve(const vector<int> &A, int L, int R)
	{
		if (L > R) return INT_MIN;
		int mid = (L + R) / 2, leftSum = 0, rightSum = 0;

		for (int i = mid - 1, curSum = 0; i >= L; i--) {
			curSum += A[i];
			leftSum = max(leftSum, curSum);
		}

		for (int i = mid + 1, curSum = 0; i <= R; i++) {
			curSum += A[i];
			rightSum = max(rightSum, curSum);
		}

		return max({solve(A, L, mid - 1), solve(A, mid + 1, R),
		            leftSum + A[mid] + rightSum});
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string _vec2str(const vector<int> &vec)
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
		int t = f->maxSubArray(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: nums = " << _vec2str(ip[i])
			     << "  output: maxSub = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<vector<int>> ip{
	    {-2, 1, -3, 4, -1, 2, 1, -5, 4},
	    {1},
	    {5, 4, -1, 7, 8},
	};

	vector<int> op{6, 1, 23};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_brute_force>(), make_shared<_02_recursive>(),
	    make_shared<_03_dp_memo>(),     make_shared<_04_dp_tab>(),
	    make_shared<_05_kadanes>(),     make_shared<_06_divide_conquer>(),
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
