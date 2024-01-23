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
 * [lc53]: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * [lcdi1]: https://leetcode.com/problems/maximum-subarray/solutions/1595195/c-python-7-simple-solutions-w-explanation-brute-force-dp-kadane-divide-conquer
 * [bd1]: https://www.baeldung.com/java-maximum-subarray
 */

#include <bits/stdc++.h>

using namespace std;

/* Time complexity: O(n^2) square
 *
 * Where n is the number of elements in nums and there are n*(n+1)/2 subarrays
 * to check.
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

/* Time complexity: O(n) linear */
int _06_kadanes_algorithm(vector<int> nums)
{
	int curr_sum = 0, sum = INT_MIN, b = 0, e = 0;
	for (int i = 0; i < nums.size(); i++) {
		curr_sum += nums[i];
		if (nums[i] > curr_sum) {
			curr_sum = nums[i];
			if (sum < curr_sum) b = i;
		}
		if (sum < curr_sum) {
			sum = curr_sum;
			e = i;
		}
	}
	b = min(b, e);
	int t = 0;
	for (int i = b; i <= e; i++) t += nums[i];
	return t == sum ? sum : INT_MIN;
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
	    /* TODO implement these variations
	    _02_recursive,
	    _03_dynamic_programming_memoization,
	    _04_dynamic_programming_tabulation,
	    _05_divide_conquer,
	    */
	    _06_kadanes_algorithm,
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
