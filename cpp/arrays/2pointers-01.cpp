/**
 * Variations of Two pointers techniques - 01
 * ==========================================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _2p_move0toEnd_desc "Move all 0 to end / right in array"

/* TC : O(n)
 * SC : O(1)
 */
void move0toEnd(span<int> a)
{
	int n = a.size();
	int j = 0;
	fii (i, n)
		if (a[i]) swap(a[j++], a[i]);
}

#define _2p_move0toBegin_desc "Move all 0 to begin / left in array"

/* TC : O(n)
 * SC : O(1)
 */
void move0toBegin(span<int> a)
{
	int n = a.size();
	int j = n - 1;
	frii (i, j)
		if (a[i]) swap(a[j--], a[i]);
}

#define _2p_rmDupsSorted_desc "Remove duplicates in sorted array"

/* TC : O(n)
 * SC : O(1)
 */
void rmDupsSorted(span<int> a)
{
	int n = a.size();
	if (n == 0 || n == 1) return;

	int j = 0;
	fii (i, n - 1)
		if (a[i] != a[i + 1]) a[j++] = a[i];
	a[j++] = a[n - 1];

	// Remove or zero all remaining elements
	for (; j < n; j++) a[j] = 0;
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(move0toEnd, _2p_move0toEnd_desc)
{
	vi_t i, a, e;
	i = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	a = i;
	e = {5, 6, 4, 6, 9, 8, 0, 0, 0};
	move0toEnd(a);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

TEST(move0toBegin, _2p_move0toBegin_desc)
{
	vi_t i, a, e;
	i = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	a = i;
	e = {0, 0, 0, 5, 6, 4, 6, 9, 8};
	move0toBegin(a);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

TEST(rmDupsSorted, _2p_rmDupsSorted_desc)
{
	vi_t i, a, e;
	i = {1, 2, 2, 3, 4, 4, 4, 5, 5};
	a = i;
	e = {1, 2, 3, 4, 5, 0, 0, 0, 0};
	rmDupsSorted(a);

	CHECK_EQ(e, a);
	SHOW_OUTPUT(i, a);
}

INIT_TEST_MAIN();
