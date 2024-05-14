// design patterns
// observer & state pattern

// exposed to client code
class BaseState
{
private:
	BaseState *state;
	BaseState *next;

public:
	BaseState *nextState() { return state->next; }
}

class StartState : public BaseState
{
private:
	BaseState *next;

public:
	setNext() { next = new RunState; }
}

class RunState : public BaseState
{
private:
	BaseState *next;

public:
	setNext() { next = new StopState; }
}

class StopState : public BaseState
{
private:
	BaseState *next;

public:
	setNext() { next = NULL; }
}

int main()
{
	BaseState *state = new StartState();
	// do some task & change state
	state = state->nextState();
	// do some task & change state
	state = state->nextState();
	return 0;
}

// factory pattern
enum VehicleType {
	Car,
	Bike
}

class Vehicle
{
public:
	virtual void run(void) = 0;
}

class Car : public Vehicle
{
public:
	void run(void) { cout << "car run" << endl; }
}

class Bike : public Vehicle
{
public:
	void run(void) { cout << "car run" << endl; }
}

class VehicleFactory
{
public:
	Vehicle *createVehicle(VehicleType vt)
	{
		switch (vt) {
		}
	}
}

int main()
{
	BaseState *state = new StartState();
	// do some task & change state
	state = state->nextState();
	// do some task & change state
	state = state->nextState();
	return 0;
}

// inheritance

class Base
{
public:
	virtual void foo();
	virtual void bar(int);
};

class Derived : public Base
{
public:
	void foo() @override; // no error
	void bar() @override; // error int is not provided
};

//===

NonCopyable() = default;
NonCopyable(const NonCopyable &) = delete;
NonCopyable &operator=(const NonCopyable &) = delete;

class AssignOp
{
public:
	AssignOp operator=(const AssignOp &other)
	{
		*this = other;
		return *this;
	}
}

AssignOp a;
AssignOp b;
b = a; // assign operator is called

// lvalue, rvalue
b = func(); // func() -> a, temp object it is rvalue

std::move(object &&c);

// lamda functions: anonymous
auto eq = [](int a, int b) { return a == b };
std::compare(list1, list2, eq);
std::compare(list1, list2, [](int a, int b) { return a == b });

// threads
int thread_func(int num)
{
	for (;;) {
		cout << num++ << endl;
		sleep(2);
	}
}

int main()
{
	int num = 5;
	std::thread t1(thread_func, num);
	t1.join();
	return 0;
}

// synchronisation:
// 1. conditional variables
// 2. mutex + locks
// 3. barriers

// templates
template <typename T> T func(T a, T b)
{
	T c = a + b;
	return c;
}

template <> T func<ClassType>(ClassType a, ClassType b)
{
	T c = a + b;
	return c;
}

// write function which takes an array and returns max value of sum with two of
// its elements
// input:  [1,2,3,4,5,6]
// output: 11

int sum_2(std::vector<int> nums)
{
	int max_sum = 0;
	for (int i = 0; i < nums.size() - 1; i++) {
		int curr_sum = 0;
		for (int j = i + 1; i < nums.size(); i++) {
			curr_sum = std::max(curr_sum, nums[i] + nums[j]);
		}
		max_sum = std::max(max_sum, curr_sum);
		;
	}
	return max_sum;
}
