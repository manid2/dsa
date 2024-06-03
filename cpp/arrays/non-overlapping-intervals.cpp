/**
 * 435. Non-overlapping Intervals
 * ==============================
 *
 * Given an array of intervals intervals where intervals[i] = [starti, endi],
 * return the minimum number of intervals you need to remove to make the rest
 * of the intervals non-overlapping.
 *
 * Tags: #arrays
 *
 * Example 1:
 *
 * Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of the intervals are
 * non-overlapping.
 *
 * Example 2:
 *
 * Input: intervals = [[1,2],[1,2],[1,2]]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of the intervals
 * non-overlapping.
 *
 * Example 3:
 *
 * Input: intervals = [[1,2],[2,3]]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're
 * already non-overlapping.
 *
 * Constraints:
 *
 *     1 <= intervals.length <= 10^5
 *     intervals[i].length == 2
 *     -5 * 10^4 <= starti < endi <= 5 * 10^4
 *
 * Solution:
 *
 * https://medium.com/swlh/non-overlapping-intervals-f0bce2dfc617
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * TC: O(N log N)
 * SC: O(1)
 */
int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
	sort(intervals.begin(), intervals.end(),
	     [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
	int c = 0;
	int p = 0, n = 1;
	for (; n < intervals.size(); n++) {
		if (intervals[p][1] > intervals[n][0]) {
			c++;
			if (intervals[p][1] > intervals[n][1]) p = n;
		} else
			p = n;
	}
	return c;
}

typedef std::function<int(std::vector<std::vector<int>> &)> func_t;

void test_impl(vector<vector<vector<int>>> ip, vector<int> op, func_t impl)
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
	vector<vector<vector<int>>> ip{
	    {{1, 2}, {2, 3}, {3, 4}, {1, 3}},
	    {{1, 20}, {2, 3}, {3, 4}, {1, 3}, {4, 5}},
	};
	vector<int> op{1, 2};
	vector<func_t> impls{
	    eraseOverlapIntervals,
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
