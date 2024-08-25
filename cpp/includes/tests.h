#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
typedef ios_base &(*io_t)(ios_base &);

struct _test {
	_test(const string &desc) : desc(desc), tc(0), off(cout.flags()) {}

	string getDesc(void) const { return desc; }
	int getTc(void) const { return tc; }
	void incTc(void) { tc++; }

	// Check test cases
	virtual void test_func(void) = 0;

	template <class... Types>
	void setIo(Types... args)
	{
		io = {args...};
	}
	vector<io_t> getIo(void) const { return io; }

	string em, am, im, om;

private:
	string desc;
	int tc;
	vector<io_t> io;
	ios::fmtflags off;
};

static vector<_test *> _tests;

// clang-format off
#define _CONCAT_WITH(x, y, sp)  x ## sp ## y
// clang-format on

#define _CONCAT_NAME(x, y) _CONCAT_WITH(x, y, _)

#define _TEST_STRUCT(name) _CONCAT_NAME(_test, name)

#define TEST(name, desc)                                                     \
	struct _TEST_STRUCT(name) : public _test {                           \
		void test_func() override;                                   \
		_TEST_STRUCT(name)() : _test(desc)                           \
		{                                                            \
			_tests.push_back(this);                              \
		}                                                            \
	};                                                                   \
	static _TEST_STRUCT(name) _CONCAT_NAME(_test_instance, name);        \
	void _TEST_STRUCT(name)::test_func()

#define RUN_ALL_TESTS()                                                      \
	size_t tc = 0, ts = 0;                                               \
	for (; ts < size(_tests); ts++) {                                    \
		if (getenv("SHOW_TEST_OUTPUT"))                              \
			cout << "Testing implementation " << ts + 1 << " "   \
			     << _tests[ts]->getDesc() << "\n";               \
		_tests[ts]->test_func();                                     \
		tc += _tests[ts]->getTc();                                   \
	}                                                                    \
	cout << "Executed " << ts << " implementations"                      \
	     << " with " << tc << " tests." << endl

#define SET_IO(...) this->setIo(__VA_ARGS__)
#define RESET_IO()  cout.flags(this->off)

#define SET_CUSTOM_FAIL_MSG(e, a)    this->em = (e), this->am = (a);
#define SET_CUSTOM_SUCCESS_MSG(i, o) this->im = (i), this->om = (o);

#define RESET_CUSTOM_MSG()                                                   \
	this->em.clear(), this->am.clear();                                  \
	this->im.clear(), this->om.clear()

#define _GET_FAIL_MSG(e, a)                                                  \
	cerr << "expected: ";                                                \
	if (this->em.empty())                                                \
		cerr << (e);                                                 \
	else                                                                 \
		cerr << this->em;                                            \
	cerr << "  ";                                                        \
	cerr << "actual: ";                                                  \
	if (this->am.empty())                                                \
		cerr << (a);                                                 \
	else                                                                 \
		cerr << this->am;                                            \
	cerr << "." << endl

#define _GET_SUCCESS_MSG(i, o)                                               \
	cout << "input: ";                                                   \
	if (this->im.empty())                                                \
		cout << (i);                                                 \
	else                                                                 \
		cout << this->im;                                            \
	cout << "  ";                                                        \
	cout << "output: ";                                                  \
	if (this->om.empty())                                                \
		cout << (o);                                                 \
	else                                                                 \
		cout << this->om;                                            \
	cout << ".\n"

#define _CHECK(op, e, a)                                                     \
	if (e op a) {                                                        \
		this->incTc();                                               \
	} else {                                                             \
		cerr << "  test-" << (this->getTc() + 1) << " failed! ";     \
		for (io_t _e : this->getIo()) cerr << _e;                    \
		_GET_FAIL_MSG(e, a);                                         \
		exit(1);                                                     \
	}

#define CHECK_EQ(e, a) _CHECK(==, (e), (a))
#define CHECK_NE(e, a) _CHECK(!=, (e), (a))

#define SHOW_OUTPUT(i, o)                                                    \
	if (getenv("SHOW_TEST_OUTPUT")) {                                    \
		cout << "  test-" << this->getTc() << ":  ";                 \
		for (io_t _e : this->getIo()) cout << _e;                    \
		_GET_SUCCESS_MSG(i, o);                                      \
	}

#define INIT_TEST_MAIN()                                                     \
	int main(int, char **)                                               \
	{                                                                    \
		RUN_ALL_TESTS();                                             \
		return 0;                                                    \
	}

/* ===========================================================================
 * Utilities
 * ===========================================================================
 */
// clang-format off
#define FOR_I2N_(i, n, type) for (type i = 0; i < (n); i++)
#define FOR_N2I_(i, n, type) for (type i = (n); i >= 0; i--)
// clang-format on

#define fii(i, n)  FOR_I2N_(i, (n), int)
#define fsi(i, n)  FOR_I2N_(i, (n), size_t)
#define frii(i, n) FOR_N2I_(i, (n), int)
#define frsi(i, n) FOR_N2I_(i, (n), size_t)

#define vi_t  vector<int>
#define vi2_t vector<vi_t>
#define umi_t unordered_map<int, int>

#define vi_v(v, n, i)  vi_t v((n), (i))
#define vi2_v(v, n, i) vi2_t v((n), vi_t((n), (i)))

template <class T>
ostream &operator<<(ostream &out, const vector<T> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) out << (i++ ? ", " : "") << e;
	out << "}";
	return out;
}

template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &c)
{
	out << "{";
	for (int i = 0; const auto &e : c) out << (i++ ? ", " : "") << e;
	out << "}";
	return out;
}

template <class T>
string to_string(const vector<T> &c)
{
	ostringstream oss;
	oss << c;
	return oss.str();
}
