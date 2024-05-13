/**
 * Accion Labs
 * ===========
 *
 * Interview - Round 1
 */

/**
 * Problem 2: Reverse a signed integer
 * ===================================
 *
 * Input: num=-123
 * Output: -321
 */
int rev_int(int num)
{
	int t = num;
	int rs = 0;
	while (t) {
		int r = t % 10;
		// check int overflow
		long l = (rs + r) * 10;
		if ((l > INT_MAX) || (l > INT_MIN)) return 0;
		t /= 10;
		rs = l;
	}
	return rs;
}
