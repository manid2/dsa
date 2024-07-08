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

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual int thirdMax(const vector<int> &nums) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n log k) for k'th largest number
 * SC : O(1)
 */
class _01_set : public _00_test
{
public:
	_01_set() : _00_test("Third max number using std::set") {}

	int thirdMax(const vector<int> &a) override
	{
		set<int> s;
		for (int e : a) {
			s.insert(e);
			if (s.size() > 3) s.erase(*s.begin());
		}
		if (s.size() == 3) return *s.begin();
		return *prev(s.end());
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

void test_impl(const vector<vector<int>> &ip, vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->thirdMax(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: nums = " << _vec2str(ip[i])
			     << "  output: num = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<vector<int>> ip{
	    {2, 3, 2, 1},
	};

	vector op{1};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_set>(),
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
