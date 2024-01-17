/**
 * Third distinct maximum number
 * ==============================
 *
 * Leetcode: [414. Third Maximum Number][lc414]
 *
 * Given an integer array nums, return the third distinct maximum number in
 * this array. If the third maximum does not exist, return the maximum number.
 *
 * Tags: #arrays, #easy
 *
 * Example 1:
 *   Input: nums = [3,2,1]
 *   Output: 1
 *
 * Example 2:
 *   Input: nums = [3,2,1]
 *   Output: 1
 *
 * Example 3:
 *   Input: nums = [2,2,3,1]
 *   Output: 1
 *
 * [lc414]: https://leetcode.com/problems/third-maximum-number/
 */

#include <bits/stdc++.h>

using namespace std;

int thirdMax(vector<int>& a) {
	set<int> m;
	for(int &e : a)
	{
		m.insert(e);
		if(m.size() > 3)
			m.erase(*m.begin());
	}

	if(m.size() == 3)
		return *m.begin();

	return *prev(m.end());
}

int main(int argc, char *argv[])
{
	vector<int> a{2, 3, 2, 1};
	cout << thirdMax(a) << endl;
	return 0;
}
