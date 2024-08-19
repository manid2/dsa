/**
 * Bit shifting more than type width
 * =================================
 *
 * Bit shifting more than the type width is Undefined Behaviour but first it
 * tries to promote the type to maximum widths of shift operands.
 *
 * GCC produces warning and the output is logical 0.
 */

#include <bitset>
#include <iomanip>
#include <iostream>

using namespace std;

template <class T>
constexpr bitset<sizeof(size_t) * 8> bits(T x)
{
	return bitset<sizeof(size_t) * 8>(x);
}

#define nbits(x) (sizeof(x) * 8)

template <class T>
inline void check(T x)
{
	if (getenv("SHOW_TEST_OUTPUT")) {
		cout << "Testing implementation " << 1 << " "
		     << "Bit shifting more than type width"
		     << "\n"
		     << "  test-0:  "
		     << "\n"
		     << "    input  x: " << bits(x)
		     << " sizeof(x): " << nbits(x) << "\n"
		     << "    output:  "
		     << "\n";

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
		cout << "       x << sizeof(x): " << bits(x << nbits(x))
		     << "\n"
		     << "       x << (sizeof(x) + 1): "
		     << bits(x << (nbits(x) + 1)) << "\n";
#pragma GCC diagnostic pop

		cout << endl;
	}
}

int main(int, char **)
{
	size_t a = 1;

	check(a);

	cout << "Executed " << 1 << " implementations"
	     << " with " << 1 << " tests." << endl;
	return 0;
}
