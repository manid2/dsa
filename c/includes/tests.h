#include <stdio.h>
#include <stdlib.h>

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
#define array_size(a) (sizeof(a) / sizeof(a[0]))

#define fii(n) for (int i = 0; i < (n); i++)

static int check_eq_n(int *l, int *r, int n)
{
	fii (n) {
		if (l[i] != r[i]) return 0;
	}
	return 1;
}

static void _a2s(int *a, int n, char *b)
{
	int l = 0, f = 1;
	b[l++] = '{';
	fii (n) {
		l += sprintf(&b[l], "%s%d", (f ? "" : ", "), a[i]);
		f = 0;
	}
	b[l++] = '}';
	b[l] = '\0';
}

#define CHECK_EQ_N(l, r, n)                                                  \
	{                                                                    \
		char ab[100], eb[100];                                       \
		_a2s(l, n, ab);                                              \
		_a2s(r, n, eb);                                              \
		if (!check_eq_n(l, r, n)) {                                  \
			fprintf(stderr,                                      \
			        "  test-%d failed! "                         \
			        "expected %s, actual %s.\n",                 \
			        tc, ab, eb);                                 \
			exit(1);                                             \
		} else {                                                     \
			if (getenv("SHOW_TEST_OUTPUT"))                      \
				fprintf(                                     \
				    stdout,                                  \
				    "  test-%d:  input: %s,  output: %s.\n", \
				    tc, ab, eb);                             \
		}                                                            \
	}

#define RUN_ALL_TESTS()                                                      \
	size_t tc = 0, ts = 0;                                               \
	for (; ts < array_size(_tests); ts++) {                              \
		if (getenv("SHOW_TEST_OUTPUT"))                              \
			fprintf(stdout, "Testing implementation %d %s\n",    \
			        ts + 1, _tests[ts].desc);                    \
		tc += _tests[ts].func();                                     \
	}                                                                    \
	fprintf(stdout, "Executed %d implementations with %d tests.", ts, tc);

typedef int (*TestFuncPtr)();

struct TestsStruct {
	const char *desc;
	TestFuncPtr func;
};

#define TEST_LIST static struct TestsStruct _tests[]

#define INIT_TEST_MAIN()                                                     \
	int main(int, char **)                                               \
	{                                                                    \
		RUN_ALL_TESTS();                                             \
		return 0;                                                    \
	}
