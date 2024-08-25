/**
 * Sorting Algorithms - 01
 * =======================
 *
 * Sorting algorithms with worst case TC O(n^2).
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/bubble-sort-in-cpp/
 * https://www.programiz.com/dsa/bubble-sort
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _sort_BubbleSort_desc "Bubble Sort"

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
namespace BubbleSort
{
void sort(vi_t &a)
{
	int n = size(a);
	fii (i, n - 1) {
		bool swapped = false;
		fii (j, n - i - 1) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}
} // namespace BubbleSort

#define _sort_SelectionSort_desc "Selection Sort"

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
namespace SelectionSort
{
void sort(vi_t &a)
{
	int n = size(a);
	fii (i, n - 1) {
		int m = i;
		for (int j = i + 1; j < n; j++) m = a[j] < a[m] ? j : m;
		swap(a[i], a[m]);
	}
}
} // namespace SelectionSort

#define _sort_InsertionSort_desc "Insertion Sort"

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
namespace InsertionSort
{
void sort(vi_t &a)
{
	int n = size(a);
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
}
} // namespace InsertionSort

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _sort_check(i, e)                                                    \
	{                                                                    \
		vi_t a = i;                                                  \
		sort(a);                                                     \
		string im = to_string(i);                                    \
		string om = to_string(a);                                    \
		string em = to_string(e);                                    \
		SET_CUSTOM_FAIL_MSG(em, om);                                 \
		SET_CUSTOM_SUCCESS_MSG(im, om);                              \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(i, a);                                           \
	}

#define _SORT_NAME(var) var
#define _SORT_DESC(var) _sort_##var##_desc

#define _SORT_TEST(var)                                                      \
	TEST(_SORT_NAME(var), _SORT_DESC(var))                               \
	{                                                                    \
		using namespace _SORT_NAME(var);                             \
		vi2_t ip{                                                    \
		    {5, 1, 4, 2, 8},                                         \
		    {-2, 45, 0, 11, -9},                                     \
		};                                                           \
		vi2_t op{                                                    \
		    {1, 2, 4, 5, 8},                                         \
		    {-9, -2, 0, 11, 45},                                     \
		};                                                           \
		int n = size(ip);                                            \
		fii (i, n) _sort_check(ip[i], op[i]);                        \
	}

_SORT_TEST(BubbleSort);
_SORT_TEST(SelectionSort);
_SORT_TEST(InsertionSort);

INIT_TEST_MAIN();
