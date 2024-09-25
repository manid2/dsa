/**
 * One producer Many Consumer
 * ==========================
 *
 * Refer:
 *
 * https://superfastpython.com/thread-producer-consumer-pattern-in-python/
 */

#include "tests.h"

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

/* shared string stream */
ostringstream os;

void producer(int id)
{
	string sp(4, ' ');
	string name = sp + format("producer {}", id);
	vi_t a(5);
	iota(begin(a), end(a), 0);
	a.push_back(-1); // sentinel object to indicate end of items
	for (int i : a) {
		{
			unique_lock<mutex> lk(mx);
			sq.push(i); // produce 1 item
			os << format("\n{}: write {}", name, i);
		}
		cv.notify_all();
		this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void consumer(int id)
{
	string sp(4, ' ');
	string name = sp + format("consumer {}", id);
	for (;;) {
		unique_lock<mutex> lk(mx);
		cv.wait(lk, []() { return !empty(sq); });
		int i = sq.front(); // consume 1 item
		sq.pop();
		os << format("\n{}: read {}", name, i);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (i == -1) {
			// add sentinel object back into queue for other
			// consumers to exit
			sq.push(-1);
			break;
		}
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
		using namespace _PC1_NAME(var);                              \
		int np = 1, nc = 2;                                          \
		vector<thread> producers, consumers;                         \
		fii (i, np) producers.emplace_back(producer, i);             \
		fii (i, nc) consumers.emplace_back(consumer, i);             \
		for (auto &x : producers) x.join();                          \
		for (auto &x : consumers) x.join();                          \
		SUCCESS();                                                   \
		string im = format("producers {}, consumers {}", np, nc);    \
		string om = os.str();                                        \
		SHOW_OUTPUT(im, om);                                         \
	}

_PC1_TEST(MutexCondVar);

INIT_TEST_MAIN();
