/**
 * Convert strings into integers & put odd ones before even
 * ========================================================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
static inline bool _is_number(const string &s)
{
	return !empty(s) && all_of(begin(s), end(s), ::isdigit);
}

static inline bool _is_odd(int n) { return n % 2; }
static inline bool _is_even(int n) { return !_is_odd(n); }

void _moveOddToBegin(vi_t &a)
{
	int l = 0, r = size(a) - 1;
	while (l < r) {
		while (_is_even(a[l]) && l < r) l++;
		while (_is_odd(a[r]) && l < r) r--;
		if (l < r) swap(a[l++], a[r--]);
	}
}

vi_t oddEvens(const vector<string> &a)
{
	vi_t ret;
	for (const auto &e : a) {
		try {
			if (_is_number(e)) ret.push_back(stoi(e));
		} catch (std::invalid_argument const &ex) {
			cerr << format("invalid argument: {}\n", ex.what());
		} catch (std::out_of_range const &ex) {
			cerr << format("out of range: {}\n", ex.what());
		}
	}
	_moveOddToBegin(ret);
	return ret;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(odd_evens, "Convert strings into integers & put odd ones before even")
{
	vector<string> i = {"9",
	                    "0",
	                    "49",
	                    "2",
	                    "100",
	                    "not a number",
	                    "12 not a number too"};
	vi_t e = {100, 0, 2, 49, 9};
	vi_t a = oddEvens(i);
	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

INIT_TEST_MAIN();