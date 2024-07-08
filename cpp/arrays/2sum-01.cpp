/**
 * Two sum - 01
 * ============
 *
 * Refer:
 *
 * https://leetcode.com/problems/two-sum/
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

	virtual vector<int> twoSum(vector<int> &nums, int target) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(n)
 */
class _01_2sum : public _00_test
{
public:
	_01_2sum() : _00_test("Two sum") {}

	vector<int> twoSum(vector<int> &a, int t) override
	{
		int n = static_cast<int>(a.size());
		unordered_map<int, int> m;
		for (int i = 0; i < n; i++) {
			int c = t - a[i];
			if (m.contains(c)) return {m[c], i};
			m[a[i]] = i;
		}
		return {};
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

void test_impl(vector<pair<vector<int>, int>> &ip, vector<vector<int>> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		vector<int> t = f->twoSum(ip[i].first, ip[i].second);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << _vec2str(op[i])
			     << ", actual " << _vec2str(t)
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
	    {{2, 7, 11, 15}, 9},
	    {{3, 2, 4}, 6},
	    {{3, 3}, 6},
	};

	vector<vector<int>> op{
	    {0, 1},
	    {1, 2},
	    {0, 1},
	};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_2sum>(),
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
