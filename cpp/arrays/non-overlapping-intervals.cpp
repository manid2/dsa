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

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual int eraseOverlapIntervals(vector<vector<int>> &intervals) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/**
 * TC: O(n log n + n)
 * SC: O(1)
 */
class _01_greedy : public _00_test
{
public:
	_01_greedy() : _00_test("Non overlapping intervals greedy") {}

	int eraseOverlapIntervals(vector<vector<int>> &intervals) override
	{
		sort(intervals.begin(), intervals.end(),
		     [](vector<int> &a, vector<int> &b) {
			     return a[0] < b[0];
		     });
		int c = 0;
		int p = 0, n = 1;
		for (; n < static_cast<int>(intervals.size()); n++) {
			if (intervals[p][1] > intervals[n][0]) {
				c++;
				if (intervals[p][1] > intervals[n][1]) p = n;
			} else
				p = n;
		}
		return c;
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
		int t = f->eraseOverlapIntervals(ip[i]);
		if (op[i] != t) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: intervals = " << _2vec2str(ip[i])
			     << "  output: min = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<vec2_t> ip{
	    {{1, 2}, {2, 3}, {3, 4}, {1, 3}},
	    {{1, 20}, {2, 3}, {3, 4}, {1, 3}, {4, 5}},
	};

	vector<int> op{1, 2};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_greedy>(),
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
