/**
 * Bit shifting more than type width
 * =================================
 *
 * Bit shifting more than the type width is Undefined Behaviour but first it
 * tries to promote the type to maximum widths of shift operands.
 *
 * GCC produces warning and the output is logical 0.
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
template <class T>
constexpr bitset<sizeof(T) * 8> bits(T x)
{
	return bitset<sizeof(T) * 8>(x);
}

#define nbits(x) (sizeof(x) * 8)
#define b2s(x)   bits(x).to_string()
#define sb(x, i) x << (nbits(x) - i)

template <class T>
T check(T x, string &im, string &om)
{
	T r;
	im = format("x: {}, sizeof(x): {}", b2s(x), nbits(x));

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
	om = format("x << (sizeof(x) - 1): {},  x << sizeof(x): {}",
	            b2s(sb(x, 1)), b2s(sb(x, 0)));
	r = sb(x, 0);
#pragma GCC diagnostic pop
	return r;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _bsg_check(T)                                                        \
	{                                                                    \
		T i = 1, a = i, e = 0;                                       \
		string im, om;                                               \
		a = check(a, im, om);                                        \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(im, om);                                         \
	}

TEST(check, "Bit shifting more than type width (undefined behavior)")
{
	_bsg_check(char);
	_bsg_check(short);
	_bsg_check(int);
	_bsg_check(size_t);
}

INIT_TEST_MAIN();
