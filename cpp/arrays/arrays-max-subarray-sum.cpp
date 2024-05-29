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

/**
 * TC: O(N^2) => For trying all possible N*(N+1)/2 sub arrays
 * SC: O(1)
 */
int _01_brute_force(vector<int> nums)
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

/**
 * TC: O(N^2) => For trying all possible N*(N+1)/2 sub arrays
 * SC: O(N)   => For recursion
 */
int _02_recursive_solve(vector<int> &A, int i, bool mustPick)
{
	if (i >= size(A)) return mustPick ? 0 : INT_MIN;
	if (mustPick)
		// either stop here or choose current element and recurse
		return max(0, A[i] + _02_recursive_solve(A, i + 1, true));
	// try both choosing current element or not choosing
	return max(_02_recursive_solve(A, i + 1, false),
	           A[i] + _02_recursive_solve(A, i + 1, true));
}

int _02_recursive(vector<int> nums)
{
	return _02_recursive_solve(nums, 0, false);
}

/**
 * TC: O(N) => For calculating 2N states and reusing memos
 * SC: O(N) => For recursion
 */
int _03_dp_recusive_solve(vector<int> &A, int i, bool mustPick,
                          vector<vector<int>> &dp)
{
	if (i >= size(A)) return mustPick ? 0 : INT_MIN;
	if (dp[mustPick][i] != -1) return dp[mustPick][i];
	if (mustPick)
		// either stop here or choose current element and recurse
		return dp[mustPick][i] =
		           max(0, A[i] + _03_dp_recusive_solve(A, i + 1, true,
		                                               dp));
	// try both choosing current element or not choosing
	return dp[mustPick][i] =
	           max(_03_dp_recusive_solve(A, i + 1, false, dp),
	               A[i] + _03_dp_recusive_solve(A, i + 1, true, dp));
}

int _03_dynamic_programming_memoization(vector<int> nums)
{
	vector<vector<int>> dp(2, vector<int>(size(nums), -1));
	return _03_dp_recusive_solve(nums, 0, false, dp);
}

/**
 * TC: O(N)
 * SC: O(N) => For dp table
 */
int _04_dynamic_programming_tabulation(vector<int> nums)
{
	// dp[i] is the maximum subarray sum ending at i
	vector<int> dp(nums);
	for (int i = 1; i < size(nums); i++)
		dp[i] = max(nums[i], nums[i] + dp[i - 1]);
	// maximum of all max subarray sums ending at i.
	return *max_element(begin(dp), end(dp));
}

/**
 * TC: O(N)
 * SC: O(1)
 */
int _05_kadanes_algorithm(vector<int> nums)
{
	int curr_sum = 0, sum = INT_MIN, b = 0, e = 0, _s = 0;
	for (int i = 0; i < nums.size(); i++) {
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

/**
 * TC: O(N log N)
 * SC: O(log N)
 *
 * Recurrence relation for this method T(N) = 2T(N/2) + O(N) as:
 *
 * - Recurring for left and right half (2T(N/2)).
 * - Calculating maximum subarray sum O(N).
 *
 * Solving this recurrence using master theorem to get TC O(N log N)
 */
int _06_dc_recusive_solve(vector<int> &A, int L, int R)
{
	if (L > R) return INT_MIN;
	int mid = (L + R) / 2, leftSum = 0, rightSum = 0;

	// leftSum = max subarray sum in [L, mid-1] and starting from mid-1
	for (int i = mid - 1, curSum = 0; i >= L; i--) {
		curSum += A[i];
		leftSum = max(leftSum, curSum);
	}

	// rightSum = max subarray sum in [mid+1, R] and starting from mid+1
	for (int i = mid + 1, curSum = 0; i <= R; i++) {
		curSum += A[i];
		rightSum = max(rightSum, curSum);
	}

	// return max of: left subarray, right subarray & mid subarry sums
	return max({_06_dc_recusive_solve(A, L, mid - 1),
	            _06_dc_recusive_solve(A, mid + 1, R),
	            leftSum + A[mid] + rightSum});
}

int _06_divide_conquer(vector<int> nums)
{
	return _06_dc_recusive_solve(nums, 0, size(nums) - 1);
}

typedef std::function<int(std::vector<int>)> func_t;

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

int main(int argc, char *argv[])
{
	vector<vector<int>> ip{
	    {-2, 1, -3, 4, -1, 2, 1, -5, 4},
	    {1},
	    {5, 4, -1, 7, 8},
	};
	vector<int> op{6, 1, 23};
	vector<func_t> impls{
	    _01_brute_force,
	    _02_recursive,
	    _03_dynamic_programming_memoization,
	    _04_dynamic_programming_tabulation,
	    _05_kadanes_algorithm,
	    _06_divide_conquer,
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
