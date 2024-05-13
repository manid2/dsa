// TietoEVRY - C++, Senior Software Engineer
// Round 1 - 2024-02-16T10:00:58+0530
// user defined with constructor + destructor

template <typename T> class Example
{
	private:
	T *data;
	int len;

	public:
	Example() : *data(NULL), len(0) {}
	Example(T d, int l) : *data(NULL), len(l)
	{
		data = new T[len];
		for (int i = 0; i < len; i++) data[i] = d;
	}
	Example(const std::initlizer_list<T> &list)
	{
		len = list.size();
		data = new T[len];
		for (int i = 0; i < len; i++) data[i] = list[i];
	}
	~Example() {}
}

int main()
{
	Example<int> ex = {1, 2, 4, 5};
	std::vector<int> nums(0, 20);
}

// class like std::string

class String
{
	private:
	char *data;
	int len;

	public:
	String() : *data(NULL), len(0) {}
	String(const String &other)
	{
		if (other.data) {
			len = other.len;
			data = new char[len];
			for (int i = 0; i < other.len; i++)
				data[i] = other.data[i];
		}
	}
	String operator=(const String &other)
	{
		if (other.data) {
			delete[] data;
			len = other.len;
			data = new char[len];
			for (int i = 0; i < other.len; i++)
				data[i] = other.data[i];
		}
		return *this;
	}
	~String() {}
}

String a("xyz");
String b(a); // copy constructor
String c("abc");
c = b;
String b = a; // copy constructor
b = a;        // assignment operator

func(String a);

// user defined class
class MapId
{
	private:
	int id;

	operator>();
	operator<();
	operator==();

	compare_func(MapId, MapId)
};

std::map<MapId, int, compare_func> m;
MapId a, b;
m[a] = 10;
m[b] = 11;

// threads: print odd & even upto 100

std::mutex mx;
std::conditional_variable cv;

static int num = 1;
static const int MAX = 100;

static inline bool is_odd(int d) { return d % 2; }

static inline bool is_even(int d) { return !is_odd(d); }

void print_odd(void)
{
	while (num <= MAX) {
		std::lock_guard<std::mutex> lk(mx);
		cv.wait(lk, is_even(num));
		cout << num++ << endl;
		cv.notify_all();
	}
}

void print_even(void)
{
	while (num <= MAX) {
		std::lock_guard<std::mutex> lk(mx);
		cv.wait(lk, is_odd(num));
		cout << num++ << endl;
		cv.notify_all();
	}
}

std::thread t1(print_odd), t2(print_even);
t1.join(), t2.join();

// linked list exchange alternate nodes
/**
Example 1:
	Input:  1 -> 2 -> 3 -> 4
	Output: 1 -> 4 -> 2 -> 3

Example 2:
	Input:  1 -> 2 -> 3 -> 4 -> 5
	Output: 1 -> 5 -> 2 -> 4 -> 3
 */

typedef struct _Node {
	int data;
	struct _Node *next;
} Node;

Node *get_end_node(Node *head, int len)
{
	Node *end = head;
	for (int i = 0; end && i < len; i++) end = end->next;
	return end;
}

Node *alternate_nodes(Node *head)
{
	int len = 0;
	for (; end; end = end->next) len++;

	Node *begin = head;
	Node *ans = begin;
	Node *tmp = ans;
	while (begin) {
		tmp = begin;
		tmp->next = get_end_node(len--);
		begin = begin->next;
		tmp = tmp->next;
	}
	return ans;
}
