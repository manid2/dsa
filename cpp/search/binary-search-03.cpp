/**
 * Binary Search - 03
 * ==================
 *
 * Binary search in sorted rotated array with duplicates.
 *
 * Refer:
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array
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

	virtual bool search(vector<int> &nums, int target) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : Best O(1), Average O(log n), Worst O(log n)
 * SC : O(1)
 */
class _01_binary_search : public _00_test
{
public:
	_01_binary_search()
	    : _00_test(
	          "Binary search in sorted rotated array with duplicates")
	{
	}

	bool search(vector<int> &a, int t) override
	{
		int l = 0, r = a.size() - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (t == a[m]) return true;
			if (a[l] == a[m] && a[m] == a[r]) {
				l++, r--;
				continue;
			}
			if (a[l] <= a[m]) {
				if (a[l] <= t && t < a[m])
					r = m - 1;
				else
					l = m + 1;
			} else {
				if (a[m] < t && t <= a[r])
					l = m + 1;
				else
					r = m - 1;
			}
		}
		return false;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string _vec2str(vector<int> &vec)
{
	ostringstream oss;
	copy(vec.begin(), vec.end() - 1, ostream_iterator<int>(oss, ", "));
	oss << vec.back();
	return oss.str();
}

void test_impl(vector<pair<vector<int>, int>> &ip, vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->search(ip[i].first, ip[i].second);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "nums = {" << _vec2str(ip[i].first) << "} "
			     << "target = " << ip[i].second << "\n";
	}
}

int main(int, char **)
{
	vector<pair<vector<int>, int>> ip{
	    {{4, 5, 6, 7, 0, 1, 2}, 0},
	    {{2, 5, 6, 0, 0, 1, 2}, 3},
	    {{1}, 0},
	    {{3, 1, 2, 3, 3, 3, 3}, 1},
	};

	vector<int> op{true, false, false, true};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_binary_search>(),
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
