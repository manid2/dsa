// multi threading: conditional variables

std::conditional_variable cv;
std::mutex mx;

int thread1(void *arg)
{
	int n = (int)*arg;
	while (cv.wait()) {
		std::unique_lock<std::mutex> l(mx);
		cout << n << endl;
		cv.notify_all();
	}
}

int main(int ac, char **av)
{
	int a = 5, b = 7;
	std::thread t1(thread1, &a);
	std::thread t2(thread1, &b);
	// do other tasks
	t1.join(); // wait for thread1 to finish
	t2.join(); // wait for thread1 to finish
	return 0;
}

//

class Test
{
public:
	Test() : d(0) {}

	Test(const Test &t)
	{
		str = t.str;
		data = t.data;
	}

	Test(string &s, int d) : str(s), data(d) {}

	Test operator=(const Test &t)
	{
		str = t.str;
		data = t.data;
		return *this;
	}

private:
	string str;
	int data;
}

// shared_ptr

int main(int ac, char **av)
{
	std::shared_ptr<char> str = std::make_shared<char>(10);
	std::unique_ptr<char> str1 = std::make_shared<char>(10);
std:;
	memcpy(str, "hello", 5); //
std:;
	memcpy(str1, "hello", 5); // error
	return 0;
}

// semaphore in c
int thread1(void *arg)
{
	int n = (int)*arg;
	while (sem_get()) {
		std::unique_lock<std::mutex> l(mx);
		cout << n << endl;
		sem_signal();
	}
}

int main(int ac, char **av)
{
	int a = 5, b = 7;
	std::thread t1(thread1, &a);
	std::thread t2(thread1, &b);
	// do other tasks
	t1.join(); // wait for thread1 to finish
	t2.join(); // wait for thread1 to finish
	return 0;
}
