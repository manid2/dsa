#include <stdio.h>

/**
 * Implement overlapping memcpy () or memmove () function
 */
static void *
_memmove(void *dst, const void *src, size_t n)
{
	char *psrc = (char *) src;
	char *pdst = (char *) dst;

	if (!psrc || !pdst)
		return NULL;

	if((psrc < pdst) && (pdst < psrc + n)) {
		// Buffer overlaps so copy backwards
		for (pdst += n, psrc += n; n--;) {
			*--pdst = *--psrc;
		}
	} else {
		// No buffer overlap so copy forwards (normal)
		while(n--) {
			*pdst++ = *psrc++;
		}
	}
	return dst;
}

int main(int argc, char *argv[])
{
    char str[] = "abcde";
    char *d = _memmove(str + 3, str, 3);
    printf ("d: %s\n", d);
    return 0;
}
