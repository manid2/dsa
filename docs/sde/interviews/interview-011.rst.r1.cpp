// Infinera - C++, Multi threading, DSA, DP
// Round 1 - 2024-02-12T14:30:00+0530

// client - server using sockets

int client()
{
	for(;;) {
		socket_ip_addr_t ip_addr; // localhost or remote
		socket_ip_addr_t ip_port; // remote port

		int fd_socket = open(); // open socket
		if (connect(fd_socket, ip_port, ip_addr)) {
			while(1) { write (fd_socket, 1, "a"); sleep (1); }
		}
		close()fd_socket;
	}
}

int server()
{
	for(;;) {
		socket_ip_addr_t ip_addr; // localhost or remote
		socket_ip_addr_t ip_port; // remote port

		int fd_socket = open(); // open socket
		if (bind(fd_socket, ip_port, ip_addr)) {
			while(1) { read (fd_socket, 5, "ab"); sleep (1); }
		}
		close()fd_socket;
	}
}

// factory pattern write a program , where vehicle is factory , and card, bike
// are 2 other classes using vehicle class

enum VehicleType {
	Bike,
	Car
}

class VehicleFactory {
public:
	Vehicle* createVehicle(enum vt) {
		switch(vt) {
		case Bike:
			return new Bike();
			break;
		case Car:
			return new Car();
			break;
		}
	}
}

class Vehicle {
}

class Bike: Vehicle {
}

class Car: Vehicle {
}

// find all odd repeated numbers
// Time  : O(n)
// Space : O(n)
std::vector<int> find_all_odd_nums(std::vector<int>& nums)
{
	std::vector<int> a;
	std::map<int, int> m;

	// O(n) to get all frequencies
	for(auto n : nums) m[n]++;

	// O(n) to get all keys with odd frequency
	for(auto [k, v]: m) if (v % 2 != 0) a.emplace_back(k);

	return a;
}

// find all odd repeated numbers
// Time  : O(n)
// Space : O(1)
std::vector<int> find_all_odd_nums(std::vector<int>& nums)
{
	int a = 0; // x ^ x = 0, x ^ 0 = x
	for(auto n : nums) {
		n ^= n;
		a = n;
	}
	return a;
}

// dynamic_cast example

class Base{}
class Derived: public Base {}

class Derived1 {}

Derived *p2 = new Derived();
Base *ptr = p2;

ptr2 = new Derived1();
Base *ptr = dynamic_cast<Derived1>(ptr2); // not related Base

// exception

class Exception {} // built in STL
class CustomException : public Exception {}

throw CustomException;

// threads to print odd, even

std::conditional_variable cv;
std::mutex mx;
int N = 10;

int print_odd(void) {
	int count = 0;	
	while(cv.wait() && count < N) {
		std::lock_gaurd<> lock(mx);
		if (count % 2) cout << count++;
		cv.notify();
	}
}

int print_even(void) {
	int count = 0;	
	while(cv.wait() && count < N) {
		std::lock_gaurd<> lock(mx);
		if (count % 2 == 0) cout << count++;
		cv.notify();
	}
}
