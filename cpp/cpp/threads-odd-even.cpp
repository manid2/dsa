/**
 * Print odd & even numbers in sync with 2 threads
 *
 * Example:
 * thread 1: 1
 * thread 2: 2
 * thread 1: 3
 * thread 2: 4
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

/* threads synchronization primitives */
std::mutex mx;
std::condition_variable cv;

/* shared data between threads */
static int sd = 1;

#define MAX_DATA 10

/* cv.wait() predicate objects don't take args */
static inline bool is_odd() { return sd % 2; }
static inline bool is_even() { return !is_odd(); }

void print_odd(int tidx)
{
	while (sd < MAX_DATA) {
		std::unique_lock<std::mutex> lk(mx);
		/* cv.wait(lock, predicate) handles spurious wake up */
		cv.wait(lk, is_even);
		std::cout << "thread " << tidx << ": " << sd++ << "\n";
		cv.notify_one();
	}
}

void print_even(int tidx)
{
	while (sd < MAX_DATA) {
		std::unique_lock<std::mutex> lk(mx);
		/* cv.wait(lock, predicate) handles spurious wake up */
		cv.wait(lk, is_odd);
		std::cout << "thread " << tidx << ": " << sd++ << "\n";
		cv.notify_one();
	}
}

int main(int, char **)
{
	int tidx[2] = {0, 1};
	std::thread t1(print_odd, tidx[0]);
	std::thread t2(print_even, tidx[1]);
	t1.join();
	t2.join();
	return 0;
}
