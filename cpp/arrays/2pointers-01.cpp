/**
 * Variations of Two pointers techniques - 01
 * ==========================================
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

// Move all 0 to right / end of array in place with same order for other
// elements

/* TC : O(n)
 * SC : O(1)
 */
void move0toEnd(span<int> a)
{
	int n = a.size();
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != 0) {
			swap(a[j++], a[i]); // Partitioning the array
		}
	}
}

// Move all 0 to left / begin of array in place with same order for other
// elements

void move0toBegin(span<int> a)
{
	int n = a.size();
	int j = n - 1;
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] != 0) {
			swap(a[j--], a[i]); // Partitioning the array
		}
	}
}

// Remove repeated / duplicates in sorted array

void removeDuplicatesSorted(span<int> a)
{
	int n = a.size();
	if (n == 0 || n == 1) return;

	int j = 0;
	for (int i = 0; i < n - 1; i++)
		if (a[i] != a[i + 1]) a[j++] = a[i];
	a[j++] = a[n - 1];

	// Remove or zero all remaining elements
	for (; j < n; j++) a[j] = 0;
}

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
template <class T>
ostream &operator<<(ostream &out, const vector<T> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) out << (i++ ? ", " : "") << e;
	out << "}";
	return out;
}

struct _00_test {
	_00_test(const string &name) : name(name) {}
	string getName(void) const { return name; }
	virtual int test_func() = 0;

private:
	string name;
};

#define CHECK_EQ(l, r)                                                       \
	if (l != r) {                                                        \
		cerr << this->getName() << ": test-" << tc + 1 << " failed!" \
		     << " expected " << e << ", actual " << a << "."         \
		     << endl;                                                \
		exit(1);                                                     \
	} else {                                                             \
		tc++;                                                        \
		if (getenv("SHOW_TEST_OUTPUT"))                              \
			cout << "  test-" << tc << ":  "                     \
			     << "input: " << a << "  output: " << e << "\n"; \
	}

vector<_00_test *> tests;

#define _TEST_FUNC(func) test_##func

#define TEST(func, name)                                                     \
	struct _TEST_FUNC(func) : public _00_test {                          \
		int test_func() override;                                    \
                                                                             \
		_TEST_FUNC(func)() : _00_test(name)                          \
		{                                                            \
			tests.push_back(this);                               \
		}                                                            \
	};                                                                   \
	_TEST_FUNC(func) _test_instance_##func;                              \
	int _TEST_FUNC(func)::test_func()

#define RUN_ALL_TESTS()                                                      \
	size_t tc = 0, ts = 0;                                               \
	for (; ts < tests.size(); ts++) {                                    \
		if (getenv("SHOW_TEST_OUTPUT"))                              \
			cout << "Testing implementation " << ts + 1 << " "   \
			     << tests[ts]->getName() << "\n";                \
		tc += tests[ts]->test_func();                                \
	}                                                                    \
                                                                             \
	cout << "Executed " << ts << " implementations"                      \
	     << " with " << tc << " tests." << endl;

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
TEST(move0toEnd, "Move all 0 to end / right in array")
{
	int tc = 0;
	vector<int> a, e;
	a = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	e = {5, 6, 4, 6, 9, 8, 0, 0, 0};
	move0toEnd(a);

	CHECK_EQ(e, a);
	return tc;
}

TEST(move0toBegin, "Move all 0 to begin / left in array")
{
	int tc = 0;
	vector<int> a, e;
	a = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	e = {0, 0, 0, 5, 6, 4, 6, 9, 8};
	move0toBegin(a);

	CHECK_EQ(e, a);
	return tc;
}

TEST(removeDuplicatesSorted, "Remove duplicates in sorted array")
{

	int tc = 0;
	vector<int> a, e;
	a = {1, 2, 2, 3, 4, 4, 4, 5, 5};
	e = {1, 2, 3, 4, 5, 0, 0, 0, 0};
	removeDuplicatesSorted(a);

	CHECK_EQ(e, a);
	return tc;
}

int main(int, char **)
{
	RUN_ALL_TESTS();
	return 0;
}
