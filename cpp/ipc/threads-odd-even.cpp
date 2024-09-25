/**
 * Print odd & even numbers in sync with 2 threads
 *
 * Example:
 * thread 1: 1
 * thread 2: 2
 * thread 1: 3
 * thread 2: 4
 */

#include "tests.h"

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

#define _th_oe_MutexCondVar_desc "Mutex & Conditional Variable"

namespace MutexCondVar
{
/* threads synchronization primitives */
mutex mx;
condition_variable cv;

/* shared data between threads */
static int sd = 1;

#define MAX_DATA 10

/* cv.wait() predicate objects don't take args */
static bool is_odd() { return sd % 2; }
static bool is_even() { return !is_odd(); }

using Predicate = function<bool()>;
vpi_t a;

void print(int tidx, Predicate pred)
{
	while (sd < MAX_DATA) {
		unique_lock<mutex> lk(mx);
		/* cv.wait(lock, predicate) handles spurious wake up */
		cv.wait(lk, pred);
		a.emplace_back(tidx, sd);
		sd++;
		cv.notify_one();
	}
}
} // namespace MutexCondVar

// TODO namespace Semaphores

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
ostream &operator<<(ostream &out, const vpi_t &c)
{
	int n = size(c);
	fii (i, n) {
		int _tidx = c[i].first, _sd = c[i].second;
		out << format("\n    thread {}: {}", _tidx, _sd);
	}
	return out;
}

#define _th_oe_desc_prefix "Threads odd even"

#define _TH_OE_NAME(var) var
#define _TH_OE_DESC(var) _th_oe_desc_prefix " - " _th_oe_##var##_desc

#define _TH_OE_TEST(var)                                                     \
	TEST(_TH_OE_NAME(var), _TH_OE_DESC(var))                             \
	{                                                                    \
		using namespace _TH_OE_NAME(var);                            \
		vpi_t e;                                                     \
		int n = MAX_DATA;                                            \
		fii (i, n) e.emplace_back(i % 2, i + 1);                     \
		int t = 0;                                                   \
		vector<thread> th;                                           \
		th.emplace_back(move(thread(print, t++, is_odd)));           \
		th.emplace_back(move(thread(print, t++, is_even)));          \
		for (auto &x : th) x.join();                                 \
		CHECK_EQ(e, a);                                              \
		SHOW_OUTPUT(n, a);                                           \
	}

_TH_OE_TEST(MutexCondVar);

INIT_TEST_MAIN();
