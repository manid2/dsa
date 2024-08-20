/**
 * Pascal's triangle
 * =================
 *
 * Refer
 *
 * https://www.geeksforgeeks.org/pascal-triangle/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* Refer
 * https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
 */
int _bc(int n, int k)
{
	int r = 1;
	if (k > n - k) k = n - k;
	fii (i, k) {
		r *= (n - i);
		r /= (i + 1);
	}
	return r;
}

#define _pt_bc_desc "using Binomial Coefficients"

/* TC : O(n^3)
 * SC : O(1)
 */
vi2_t bc_pascalsTriangle(int n)
{
	vi2_v(a, n, 0);
	fii (i, n)
		fii (j, (i + 1)) a[i][j] = _bc(i, j);
	return a;
}

#define _pt_dp_desc "using Dynamic Programming"

/* TC : O(n^2)
 * SC : O(n^2)
 */
vi2_t dp_pascalsTriangle(int n)
{
	vi2_v(a, n, 0);
	fii (i, n) {
		fii (j, (i + 1)) {
			if (!j || j == i)
				a[i][j] = 1;
			else
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
		}
	}
	return a;
}

#define _pt_dp2_desc "using Dynamic Programming space optimized"

/* TC : O(n^2)
 * SC : O(1)
 */
vi2_t dp2_pascalsTriangle(int n)
{
	vi2_v(a, n, 0);
	fii (i, n) {
		int c = 1, x, y;
		for (int j = 0; j <= i; j++) {
			a[i][j] = c;
			x = i + 1, y = j + 1;
			c = c * (x - y) / y;
		}
	}
	return a;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _PRE_TEST()                                                          \
	const int n = 5;                                                     \
	vi2_t e = {                                                          \
	    {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 2, 1, 0, 0},               \
	    {1, 3, 3, 1, 0}, {1, 4, 6, 4, 1},                                \
	}

#define _pt_desc_prefix "Pascal triangle"

#define _PT_NAME(ver) ver##_pascalsTriangle
#define _PT_DESC(ver) _pt_desc_prefix " " _pt_##ver##_desc

#define _PT_TEST(ver)                                                        \
	TEST(_PT_NAME(ver), _PT_DESC(ver))                                   \
	{                                                                    \
		_PRE_TEST();                                                 \
		vi2_t a = _PT_NAME(ver)(n);                                  \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(n, a);                                           \
	}

_PT_TEST(bc);
_PT_TEST(dp);
_PT_TEST(dp2);

INIT_TEST_MAIN();
