/**
 * Benison Technologies interview
 * Senior Software Engineer
 * DPDK: C & Python
 * Round 1
 * 2024-01-17T15:49:08+0530
 */

/** print int array using char* */

int convert_char_to_int(char *p)
{
	int n = 0;
	for (size_t i = 0; i < sizeof(int); i++) {
		// handle endianess: big endian / little endian
		n += i * 10 + *p++;
	}
}

int print_int_array_using_char_ptr(void)
{
	int a[] = {2000, 3000, 4000, 5000, 8000};
	char *p = a;

	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
		int n = convert_char_to_int(p);
		printf("%d\n", n);
		p += i * sizeof(int);
	}
}

/** remove repeated characters from string */
char *remove_repeated_chars(char *s)
{
	int m[128];
	size_t l = strlen(s);
	char *t = (char *)malloc(l);

	for (size_t i = 0, j = 0; i < l; i++)
		if (m[tolower(s[i])]++ > 1) continue;
	t[j++] = s[i];
	return t;
}

/**
 * Swap num bits at positions p1, p2
 *
 * input: 0101 1101 1011, nbits=3, p1=1, p2=9
 */
int swap_nbits_p1p2(int num, int nbits, int p1, int p2)
{
	int mask = 0;
	for (int i = 0; i < nbits; i++) mask |= 1;
	n1 = num & (mask << p1); // 101
	n2 = num & (mask << p2); // 010
	num &= n1;
	num &= n2;
	return num;
}
