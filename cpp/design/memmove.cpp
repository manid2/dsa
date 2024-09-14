/**
 * Memmove with overlapping range
 * ==============================
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
void _memmove(void *dst, const void *src, size_t n)
{
	char *s = (char *)src, *d = (char *)dst;
	if (!s || !d) return;
	if ((s < d) && (d < s + n)) {
		// Buffer overlaps so copy backwards
		for (d += n, s += n; n--;) *--d = *--s;
	} else {
		// No buffer overlap so copy forwards (normal)
		while (n--) *d++ = *s++;
	}
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(_memmove, "Memmove with overlapping range")
{
	const int n = 3;
	char s[] = "abcde";
	string i(s), e(s, n);

	char *d = s + n;
	_memmove((void *)d, (void *)s, n);

	string a(d, n);
	CHECK_EQ(e, a);

	int di = d - s - 1, si = s - &s[0];
	string im;
	im += format("arr = {}, dst = {}, src = {}, size = {}", i, di, si, n);
	SHOW_OUTPUT(im, a);
}

INIT_TEST_MAIN();
