/**
 * Reverse of bits & bytes
 * =======================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n)
 * SC : O(1)
 */
// Reverse int by k bits
uint64_t reverseKBits(const uint64_t n, const uint32_t k)
{
	uint64_t r = 0, t = n;
	const uint64_t m = (1UL << k) - 1;
	while (t) {
		r <<= k;
		r |= (t & m);
		t >>= k;
	}
	return r;
}

uint64_t reverseKBytes(const uint64_t n, const uint32_t k)
{
	const uint32_t _k = sizeof(char) * 8 * k;
	return reverseKBits(n, _k);
}

uint64_t reversePairsOfBytes(const uint64_t n) { return reverseKBytes(n, 2); }

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(reversePairsOfBytes, "Reverse pairs of bytes")
{
	const uint64_t n = 0x1122'3344'5566'7788;
	const uint64_t e = 0x7788'5566'3344'1122;
	const uint64_t a = reversePairsOfBytes(n);

	SET_IO(hex);
	CHECK_EQ(e, a);
	SHOW_OUTPUT(n, a);
}

INIT_TEST_MAIN();
