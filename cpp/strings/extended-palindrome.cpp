/**
 * Extended palindrome
 * ===================
 *
 * Refer:
 *
 * https://thejoboverflow.com/problem/337/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define def_is_palin(T)                                                      \
	bool _is_palindrome(const T &s)                                      \
	{                                                                    \
		T::const_iterator l, m;                                      \
		T::const_reverse_iterator r;                                 \
		l = begin(s), m = l + size(s) / 2, r = rbegin(s);            \
		return equal(l, m, r);                                       \
	}

def_is_palin(string);
def_is_palin(vector<string>);

bool _iscp(string s, int d)
{
	size_t cs = s.size() / d;
	size_t c = 0;
	vector<string> l;
	for (size_t i = 0; i < cs; i++, c += d) {
		string p(s.begin() + c, s.begin() + c + d);
		l.push_back(p);
	}
	return _is_palindrome(l);
}

int extendedPalindrome(string &s)
{
	if (_is_palindrome(s)) return 1;
	// get prime divisor of |s| or 1
	size_t d = 1;
	for (size_t i = 2; i < s.size(); i++) {
		if ((s.size() % i) == 0) {
			d = i;
			break;
		}
	}
	if (_iscp(s, d)) return d;
	return -1;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(extendedPalindrome, "Extended palindrome")
{
	vector<string> _i = {"radar", "abcxyzabc", "microsoft"};
	vi_t _e = {1, 3, -1};
	int n = size(_i);
	fii (i, n) {
		string &s = _i[i];
		int a = extendedPalindrome(s);
		CHECK_EQ(_e[i], a);
		SHOW_OUTPUT(s, a);
	}
}

INIT_TEST_MAIN();