// CommVault round 2
// generate prime numbers

// mutex
// conditional variables

int print_prime_number()
{
	int i = 0;
	for (;;) {
		if (stop_signal) continue;
		if (is_prime(i)) fprintf(fd, "%d\n", i);
	}
}
}

int update_ui()
{
	sigset_t st;
	sigaction_t stop_signal
}

int main()
{
	update_ui();          // thread 1
	print_prime_number(); // thread 2
}

// async program
int async_print_prime_number()
{
	int i = 0;
	for (;;) {
		if (stop_signal) continue;
		if (is_prime(i)) fprintf(fd, "%d\n", i);
	}
}
}

int async_update_ui()
{
	sigset_t st;
	sigaction_t stop_signal;
	async_pause(async_print_prime_number);
	// after servicing ui action
	async_start(async_print_prime_number);
}

int main()
{
	async_update_ui();          // thread 1
	async_print_prime_number(); // thread 2
}

// conditional variable
std::mutex mx;
std::conditional_variable cv;

static int sd = 0;

int print_odd()
{
	while (1) {
		std::unique_locak<std::mutex> lk(mx);
		cv.wait(lk, []() { return sd % 2 }); // handles spurious wakes
		cout << sd << endl;
		cv.notify_all();
	}
}

int main()
{
std:;
	thread t1(print_odd, nullptr); // thread 1

	while (1) {
		std::unique_locak<std::mutex> lk(mx);
		cv.wait(lk); // handles spurious wakes
		sd++;
		cv.notify_all();
	}

	t1.join();
}
