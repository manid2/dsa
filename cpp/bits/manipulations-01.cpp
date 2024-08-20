/**
 * Bit manipulations - 01
 * ======================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

// Toggle bits between start and end positions
uint64_t toggleBitsBetween(const uint64_t num, const int start, const int end)
{
	// mask of 1's from start to end positions
	uint64_t mask = ((1UL << (end - start + 1)) - 1) << start;

	// XOR of a bit with 1 inverts / toggles / flips it
	// 0 ^ 1 = 1
	// 1 ^ 1 = 0
	return num ^ mask;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(toggleBitsBetween, "Toggle bits between start & end")
{
	const int start = 1, end = 3;
	const uint64_t n = 0b101101;
	const uint64_t e = 0b100011;
	const uint64_t a = toggleBitsBetween(n, start, end);

	auto _b2s = [](const uint64_t b) -> string {
		return bitset<8>(b).to_string();
	};

	string im = format("n = {}, start = {}, end {}", _b2s(n), start, end);

	SET_CUSTOM_FAIL_MSG(_b2s(e), _b2s(a));
	SET_CUSTOM_SUCCESS_MSG(im, _b2s(a));

	CHECK_EQ(e, a);

	SHOW_OUTPUT(n, a);
	RESET_CUSTOM_MSG();
}

INIT_TEST_MAIN();
