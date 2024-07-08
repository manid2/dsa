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

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual int firstMissingPositive(vector<int> &nums) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
class _01_firstMissingPositive : public _00_test
{
public:
	_01_firstMissingPositive() : _00_test("First missing positive") {}

	int firstMissingPositive(vector<int> &a) override
	{
		int n = a.size();
		for (int i = 0; i < n; i++)
			while (a[i] > 0 && a[i] <= n && a[a[i] - 1] != a[i])
				swap(a[i], a[a[i] - 1]);

		for (int i = 0; i < n; i++)
			if (a[i] != i + 1) return i + 1;
		return n + 1;
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

void test_impl(vector<vector<int>> &ip, vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->firstMissingPositive(ip[i]);
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
	    {1, 2, 0},
	    {3, 4, -1, 1},
	    {7, 8, 9, 11, 12},
	};

	vector op{3, 2, 1};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_firstMissingPositive>(),
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
