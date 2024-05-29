/**
 * Missing smallest positive number in unsorted array
 * ==================================================
 *
 * Leetcode: [41. First Missing Positive][lc41]
 *
 * Given an unsorted integer array find missing smallest positive number. Can
 * modify the original array.
 *
 * Complexities:
 *   Time  : O(n)
 *   Space : O(1)
 *
 * Tags: #arrays, #hard
 *
 * Example 1:
 *
 * Input: nums = [1,2,0]
 * Output: 3
 * Explanation: The numbers in the range [1,2] are all in the array.
 *
 * Example 2:
 *
 * Input: nums = [3,4,-1,1]
 * Output: 2
 * Explanation: 1 is in the array but 2 is missing.
 *
 * Example 3:
 *
 * Input: nums = [7,8,9,11,12]
 * Output: 1
 * Explanation: The smallest positive integer 1 is missing.
 *
 * Solution
 * --------
 *
 * Put each number in its right place i.e. for number 5 swap it with a[4]. At
 * last, the first place where its number is not right, return the place + 1.
 *
 * [lc41]: https://leetcode.com/problems/first-missing-positive/
 */

#include <bits/stdc++.h>

using namespace std;

int firstMissingPositive(vector<int> &a)
{
	int n = a.size();
	for (int i = 0; i < n; i++)
		while (a[i] > 0 && a[i] <= n && a[a[i] - 1] != a[i])
			swap(a[i], a[a[i] - 1]);

	for (int i = 0; i < n; i++)
		if (a[i] != i + 1) return i + 1;
	return n + 1;
}

int main(int argc, char *argv[])
{
	vector<vector<int>> ip{{1, 2, 0}, {3, 4, -1, 1}, {7, 8, 9, 11, 12}};
	vector op{3, 2, 1};

	for (size_t i = 0; i < ip.size(); i++) {
		int t = firstMissingPositive(ip[i]);
		if (op[i] != t) {
			cerr << "test failed: expected " << op[i]
			     << ", actual" << t << endl;
			return 1;
		}
		cout << t << endl;
	}
	return 0;
}
