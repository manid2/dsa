// convert string to int
char ch[] = "123";
int n; //

int str_to_int(string &s) // "123"
{
	int n = 0;
	for (auto c : s) n = (c - '0') + n * 10;
	return n;
}

unsigned char ch = 0xAA;
ch = ~ch;

int inv_nbits(uchar_t ch, int nbits)
{
	uchar_t c1 = ch, b = 0;
	for (int i = 0; i < nbits; i++) {
		b &= (1 << i); // extract bit
		b ^= (1 << i); // xor this bit to invert
		c1 |= b;       // add inverted it back to original number
	}
	return c1;
}

/* trace logic

ch = 0xAA; // 1010 1010
b = 0;

for
i = 0 : mask = 0001, c1 = 1010,
0001 ^ 1010 = 1
// 1 ^ 1 = 0
// 1 ^ 0 = 1

// extract bit
// b=1010, m=0001, b=0
// c1=1010, b=1, c1 = 1011
// c1=1010, b=10, c1 = 1011

// 2 buffers
char a[],
b[];
int nbytes = 10; // dynamic
char *start = 0, *end = 0;
*/

while (1) {
	start = a;
	memcpy(a, b, a + nbytes);
	end = a + nbytes;
}
