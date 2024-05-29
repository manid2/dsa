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

int minParens(const string &s)
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

int main(int argc, char *argv[])
{
	vector ip{"())", "((("};
	vector op{1, 3};

	for (size_t i = 0; i < ip.size(); i++) {
		int t = minParens(ip[i]);
		if (op[i] != t) {
			cerr << "test failed: expected " << op[i]
			     << ", actual" << t << endl;
			return 1;
		}
		cout << t << endl;
	}
	return 0;
}
