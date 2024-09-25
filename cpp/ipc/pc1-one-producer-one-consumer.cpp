/**
 * One producer One Consumer
 * =========================
 *
 * Refer:
 *
 * https://superfastpython.com/thread-producer-consumer-pattern-in-python/
 */

#include "tests.h"
#include <syncstream>

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */
#define _pc1_MutexCondVar_desc "Mutex & Conditional Variable"

namespace MutexCondVar
{
/* threads synchronization primitives */
mutex mx;
condition_variable cv;

/* shared queue between threads */
queue<int> sq;

void producer(int id, osyncstream &out)
{
	string name = format("producer {}", id);
	vi_t a(5);
	iota(begin(a), end(a), 0);
	a.push_back(-1); // sentinel object to indicate end of items
	for (int i : a) {
		{
			lock_guard<mutex> lk(mx);
			sq.push(i); // produce 1 item
			out << format("{}: write {}", name, i);
		}
		cv.notify_one();
	}
}

void consumer(int id, osyncstream &out)
{
	string name = format("consumer {}", id);
	for (;;) {
		unique_lock<mutex> lk(mx);
		cv.wait(lk, []() { return !empty(sq); });
		int i = sq.front(); // consume 1 item
		sq.pop();
		out << format("{}: read {}", name, i);
		if (i == -1) break; // exit on finding sentinel object
	}
}
} // namespace MutexCondVar

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _pc1_desc_prefix "Threads: One producer one consumer"

#define _PC1_NAME(var) var
#define _PC1_DESC(var) _pc1_desc_prefix " - " _pc1_##var##_desc

#define _PC1_TEST(var)                                                       \
	TEST(_PC1_NAME(var), _PC1_DESC(var))                                 \
	{                                                                    \
		/* synchronized stream */                                    \
		osyncstream out(ostringstream);                              \
		using namespace _PC1_NAME(var);                              \
		int np = 1, nc = 1;                                          \
		vector<thread> producers(np);                                \
		vector<thread> consumers(nc);                                \
		producers.push_back(thread(producer, np--, out));            \
		consumers.push_back(thread(consumer, nc--, out));            \
		for (auto &x : producers) x.join();                          \
		for (auto &x : consumers) x.join();                          \
		out.emit();                                                  \
		SUCCESS();                                                   \
		string im = format("producers {}, consumers {}", np, nc);    \
		string om = out.get_wrapped().str();                         \
		SHOW_OUTPUT(im, om);                                         \
	}

_PC1_TEST(MutexCondVar);

INIT_TEST_MAIN();
