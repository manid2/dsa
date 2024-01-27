#include <stdio.h>

// popcount algorithm
int count_set_bits_popcount(int i)
{
	i = i - ((i >> 1) & 0x55555555);                // add pairs of bits
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333); // quads
	i = (i + (i >> 4)) & 0x0F0F0F0F;                // groups of 8
	i *= 0x01010101; // horizontal sum of bytes

	// return just that top byte (after truncating to 32-bit even
	// when int is wider than uint32_t)
	return i >> 24;
}

int main(int argc, char *argv[])
{
	for (int i = 0; i < 10; i++)
		printf("i: %d, b: %d\n", i, count_set_bits_popcount(i));
	return 0;
}
