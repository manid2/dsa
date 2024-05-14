// Concentrix C++ round 2
// Singleton pattern
class Test
{
public:
	static int num;
	int &rnum;
	int *pnum;

	static Test *getObject(void)
	{
		// use mutex to gaurd
		if (!this_obj) {
			this_obj = new Test; // check if already created
		}
		return this_obj;
	}

private:
	Test *this_obj;
	Test() : rnum(0), pnum(0) {}
	Test(const Test &t);
	Test operator=(const Test &t);
}

int Test::num = 0;

int main(int ac, char **av)
{
	std::thread t1, t2;
	Test obj1 = Test::getObject();
	return 0;
}

// map
int main(int ac, char **av)
{
	std::thread t1, t2;
	Test obj1 = Test::getObject();
	return 0;
}

class TestDerived : public Test
{
}

class TestDer2;

// cast operators
int main(int ac, char **av)
{
	char b = 10;
	int a = static_cast<int>(b);

	Test *ptr = new TestDerived();
	TestDerived *ptr2 = dynamic_cast<TestDerived>(ptr); // no error
	TestDerived *ptr3 = dynamic_cast<TestDer2>(ptr);    // error

	const char cb = 10;
	char b1 = const_cast<char>(cb);

	TestDerived *ptr3 = reinterpret_cast<TestDer2>(ptr); // no error
	return 0;
}

// function override
class TestBase
{
public:
	int num;
	virtual int add(int a) { return num + a; }
	vritual ~TestBase()
}

class TestDerived : public TestBase
{
public:
	int add(int a) override { return num + a + 2; }
}

// object overload
class TestBase
{
public:
	virtual int operator()(int a) { return num + a; }
}

// vptr
