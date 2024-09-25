/**
 * One producer One Consumer
 * =========================
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

// Shared buffer and synchronization primitives
queue<pair<int, double>> buffer;
mutex mtx;
condition_variable cv;
bool done = false;

// Producer function
void producer()
{
	cout << "Producer: Running\n";
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);

	for (int i = 0; i < 10; ++i) {
		double value = dis(gen);
		this_thread::sleep_for(chrono::duration<double>(value));
		unique_lock<mutex> lock(mtx);
		buffer.push({i, value});
		cout << ">producer added (" << i << ", " << value << ")\n";
		cv.notify_all();
	}

	unique_lock<mutex> lock(mtx);
	done = true;
	cv.notify_all();
	cout << "Producer: Done\n";
}

// Consumer function
void consumer()
{
	cout << "Consumer: Running\n";
	while (true) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [] { return !buffer.empty() || done; });
		if (!buffer.empty()) {
			auto item = buffer.front();
			buffer.pop();
			lock.unlock();
			this_thread::sleep_for(
			    chrono::duration<double>(item.second));
			cout << ">consumer got (" << item.first << ", "
			     << item.second << ")\n";
		} else if (done) {
			break;
		}
	}
	cout << "Consumer: Done\n";
}

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
_pc1_test(MutexCondVar);

INIT_TEST_MAIN();
