/**
 * Minimum parentheses required to valid
 * =====================================
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/minimum-number-of-parentheses-to-be-added-to-make-it-valid/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
int minParens(const string &s)
{
	if (empty(s)) return 0;
	int n = size(s), res = 0;

	/* bal is freq of ‘(‘ - freq of ‘)’
	 * when bal is:
	 * o)  0 string is valid
	 * o)  -ve add ‘(‘ at front
	 * o)  +ve add ‘)‘ at rear
	 */
	int bal = 0;
	for (int i = 0; i < n; i++) {
		bal += (s[i] == '(' ? 1 : -1);
		if (bal == -1) bal++, res++;
	}
	return bal + res;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _mp_minParens_check(i, e)                                            \
	{                                                                    \
		int a = minParens(i);                                        \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

TEST(minParens, "Minimum parentheses required to valid")
{
	vector<string> ip{{"())"}, {"((("}};
	vi_t op{1, 3};
	int n = size(ip);
	fii (i, n) _mp_minParens_check(ip[i], op[i]);
}

INIT_TEST_MAIN();
