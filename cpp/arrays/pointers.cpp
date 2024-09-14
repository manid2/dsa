/**
 * Pointer operators precedence
 * ============================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _fmt(i, v) format("\n    index: {}, value: {}", i, v)

vi_t ptrOpPrec(const int n, string &am)
{
	int *p = (int *)malloc(n * sizeof(int)), *a = p;
	fii (i, n) *(p + i) = i;

	ostringstream out;
	out << _fmt(0, *p++);   // *a -> index: 0, value: 0, ptr++
	out << _fmt(1, (*p)++); // *a -> index: 1, value: 1, val++
	out << _fmt(1, *p);     // *a -> index: 1, value: 2
	out << _fmt(2, *++p);   // *a -> index: 2, value: 2, ++ptr
	out << _fmt(2, ++*p);   // *a -> index: 2, value: 3, ++val
	// indices: 3, 4 with values: 3, 4 are unmodified
	vi_t ret(a, a + n);
	out << format("\n    after: {}", to_string(ret));
	free(a);
	am = out.str();
	return ret;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(ptrOpPrec, "Pointer operators precedence")
{
	const int n = 5;
	string am;
	vi_t e = {0, 2, 3, 3, 4};
	vi_t a = ptrOpPrec(n, am);
	CHECK_EQ(e, a);
	SHOW_OUTPUT(n, am);
}

INIT_TEST_MAIN();
