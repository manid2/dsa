#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
typedef std::ios_base &(*io_t)(std::ios_base &);

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

private:
	string desc;
	int tc;
	vector<io_t> io;
	ios::fmtflags off;
};

static vector<_test *> _tests;

#define _TEST_STRUCT(name) _test_##name

#define TEST(name, desc)                                                     \
	struct _TEST_STRUCT(name) : public _test {                           \
		void test_func() override;                                   \
		_TEST_STRUCT(name)() : _test(desc)                           \
		{                                                            \
			_tests.push_back(this);                              \
		}                                                            \
	};                                                                   \
	static _TEST_STRUCT(name) _test_instance_##name;                     \
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
	     << " with " << tc << " tests." << endl;

#define SET_IO(...) this->setIo(__VA_ARGS__)
#define RESET_IO()  cout.flags(this->off)

#define _CHECK(op, e, a)                                                     \
	if (e op a) {                                                        \
		this->incTc();                                               \
	} else {                                                             \
		cerr << "  test-" << (this->getTc() + 1) << " failed! ";     \
		for (io_t _e : this->getIo()) cerr << _e;                    \
		cerr << "expected " << (e) << ", actual " << (a) << "."      \
		     << endl;                                                \
		exit(1);                                                     \
	}

#define CHECK_EQ(e, a) _CHECK(==, (e), (a))
#define CHECK_NE(e, a) _CHECK(!=, (e), (a))

#define SHOW_OUTPUT(i, o)                                                    \
	if (getenv("SHOW_TEST_OUTPUT")) {                                    \
		cout << "  test-" << this->getTc() << ":  ";                 \
		for (io_t _e : this->getIo()) cout << _e;                    \
		cout << "input: " << (i) << "  "                             \
		     << "output: " << (o) << "\n";                           \
	}

#define INIT_TEST_MAIN()                                                     \
	int main(int, char **)                                               \
	{                                                                    \
		RUN_ALL_TESTS();                                             \
		return 0;                                                    \
	}
