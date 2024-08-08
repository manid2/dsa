
#include <bits/stdc++.h>

using namespace std;

// Reverse in pairs of bytes

uint64_t reversePairs(uint64_t num)
{
	uint64_t result = 0;
	while(num) {
		result <<= 16;
		result |= (num & 0xFFFF);
		num >>= 16;
	}
	return result;
}

// Reverse int by k bits

uint64_t reverseKBits(uint64_t n, unsigned int k)
{
	uint64_t r = 0;
	const uint64_t m = (1U << k) - 1;
	while (n) {
		r <<= k;
		r |= (n & m);
		n >>= k;
	}
	return r;
}

int main(int, char **)
{
	// input: 0x1122 3344 5566 7788
	uint64_t n = 0x1122334455667788, r = 0;

	// output: 0x7788 5566 3344 1122
	r = reversePairs(n);
	cout << hex << r << endl;

	// output: 0x7788 5566 3344 1122
	r = reverseKBits(n, 16);
	cout << hex << r << endl;

	cout << "Executed " << 1 << " implementations"
	     << " with " << 1 << " tests." << std::endl;
	return 0;
}
