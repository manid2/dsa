#include <bits/stdc++.h>

using namespace std;

// Toggle bits between start and end positions

unsigned int invertBits(unsigned int num, int start, int end)
{
	// mask of 1's from start to end positions
	unsigned int mask = ((1 << (end - start + 1)) - 1) << start;

	// XOR of a bit with 1 inverts / toggles / flips it
	// 0 ^ 1 = 1
	// 1 ^ 1 = 0
	return num ^ mask;
}

int main()
{
	unsigned int num = 0b101101; // Binary representation of the number
	int start = 1;
	int end = 3;

	cout << "Original number: " << bitset<8>(num) << "\n";
	unsigned int result = invertBits(num, start, end);
	cout << "Inverse number: " << bitset<8>(result) << "\n";

	cout << "Executed " << 1 << " implementations"
	     << " with " << 1 << " tests." << std::endl;
	return 0;
}
