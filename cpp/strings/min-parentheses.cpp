/**
 * Minimum parentheses required to valid
 * ======================================
 *
 * Given a string of parentheses ‘(‘ or ‘)’ find the minimum number of
 * parentheses required to make the string valid.
 *
 * Tags: #strings, #easy
 *
 * Example 1:
 *
 * Input: "())"
 * Output: 1
 * Explanation: 1 '(' is required at beginning.
 *
 * Example 2:
 *
 * Input: "((("
 * Output: 3
 * Explanation: 3 ')' are required at end.
 *
 * Solution
 * --------
 *
 * Track balance of parentheses i.e. the number of ‘(‘ minus number of ‘)’ to
 * know if a string is valid i.e. balance is 0.
 *
 * If string is not balanced i.e. not 0 then:
 *   case 1: If balance negative (-1) then add 1 ‘(‘ at beginning.
 *   case 2: If balance is positive (N) then add N  ‘)‘ at beginning.
 *
 * https://www.geeksforgeeks.org/minimum-number-of-parentheses-to-be-added-to-make-it-valid/
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

	virtual int minParens(string str) = 0;

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
class _01_iterative : public _00_test
{
public:
	_01_iterative()
	    : _00_test("Minimum parentheses required to valid - Iterative")
	{
	}

	int minParens(string s) override
	{
		if (s.empty()) return 0;
		int b = 0, r = 0;
		for (size_t i = 0; i < s.size(); i++) {
			b += (s[i] == '(' ? 1 : -1);
			if (b == -1) {
				b++;
				r++;
			}
		}
		return b + r;
	}
};

class _02_stack;
class _03_string;

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
void test_impl(const vector<string> &ip, const vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->minParens(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: str = " << ip[i]
			     << "  output: min = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<string> ip{{"())"}, {"((("}};
	vector<int> op{1, 3};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_iterative>(),
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
