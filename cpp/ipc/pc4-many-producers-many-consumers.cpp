/**
 * Many producers Many Consumers
 * ============================
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
#define _pcmn_MutexCondVar_desc "Mutex & Conditional Variable"

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
    for (int i : a) {
        {
            unique_lock<mutex> lk(mx);
            sq.push(i); // produce 1 item
            os << format("\n{}: write {}", name, i);
        }
        cv.notify_one();
        //this_thread::sleep_for(std::chrono::milliseconds(500));
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
        
        if (i == -1) {
            os << format("\n{}: received sentinel, exiting", name);
            break; // exit on finding sentinel object
        }
        
        os << format("\n{}: read {}", name, i);
        //this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
} // namespace MutexCondVar

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
#define _pcmn_desc_prefix "Threads: Many producers many consumers"

#define _PCMN_NAME(var) var
#define _PCMN_DESC(var) _pcmn_desc_prefix " - " _pcmn_##var##_desc

#define _PCMN_TEST(var)                                                      \
    TEST(_PCMN_NAME(var), _PCMN_DESC(var))                                \
    {                                                                    \
        using namespace _PCMN_NAME(var);                              \
        int np = 3, nc = 3;                                          \
        vector<thread> producers, consumers;                         \
        fii (i, np) producers.emplace_back(producer, i);             \
        fii (i, nc) consumers.emplace_back(consumer, i);             \
        for (auto &x : producers) x.join();                          \
        {                                                            \
            unique_lock<mutex> lk(mx);                               \
            fii (i, nc) sq.push(-1);                                 \
        }                                                            \
        cv.notify_all();                                             \
        for (auto &x : consumers) x.join();                          \
        SUCCESS();                                                   \
        string im = format("producers {}, consumers {}", np, nc);    \
        string om = os.str();                                        \
        SHOW_OUTPUT(im, om);                                         \
    }

_PCMN_TEST(MutexCondVar);

INIT_TEST_MAIN();