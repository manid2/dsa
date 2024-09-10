/**
 * Third distinct maximum number
 * ==============================
 *
 * Refer:
 *
 * https://leetcode.com/problems/third-maximum-number/
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n log k) for k'th largest number
 * SC : O(1)
 */
int thirdMax(const vi_t &a)
{
	set<int> s;
	for (int e : a) {
		s.insert(e);
		if (s.size() > 3) s.erase(*s.begin());
	}
	if (s.size() == 3) return *s.begin();
	return *prev(s.end());
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(thirdMax, "Third distinct maximum number")
{
	vi_t i{2, 3, 2, 1};
	int e = 1;
	int a = thirdMax(i);
	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

INIT_TEST_MAIN();