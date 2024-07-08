/**
 * Binary Search - 01
 * ==================
 *
 * Binary search algorithm with worst case TC O(log n).
 *
 * Refer:
 *
 * https://leetcode.com/problems/binary-search/
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

	virtual int search(vector<int> &nums, int target) = 0;

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
	_01_binary_search() : _00_test("Binary search") {}

	int search(vector<int> &a, int t) override
	{
		int l = 0, r = a.size() - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (t == a[m])
				return m;
			else if (t < a[m])
				r = m - 1;
			else
				l = m + 1;
		}
		return -1;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string _vec2str(vector<int> &vec)
{
	ostringstream oss;
	oss << "{";
	copy(vec.begin(), vec.end() - 1, ostream_iterator<int>(oss, ", "));
	oss << vec.back();
	oss << "}";
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
			     << "input: nums = " << _vec2str(ip[i].first)
			     << ", target = " << ip[i].second
			     << "  output: index = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<pair<vector<int>, int>> ip{
	    {{-1, 0, 3, 5, 9, 12}, 9},
	    {{-1, 0, 3, 5, 9, 12}, 2},
	};

	vector<int> op{4, -1};

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
