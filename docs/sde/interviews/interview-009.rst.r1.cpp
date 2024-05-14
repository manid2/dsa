// Round 1 - 2=024-02-05T16:00:31+0530

// struct c
typedef struct node {
	int data1;
	int data2;
	char data3;
} node_t;

int main(int ac, char &av)

    int main(int ac, char **av)
{
	node_t *n = (node_t *)malloc(5 * sizeof(node_t));
	n[0]->data = 5;
	printf("%d\n", n->data);
	n = (node_t *)realloc(10 * sizeof(node_t));
	free(n);
	return 0;
}

// memory

/*
High->program args->stack->free meory |
    stack pointer meets heap pointer->heap
        ->bss
        segment(uninitlized global &static variables)
        ->data segment(initilized global &static variables)
        ->read,
    read - write areas low->code.text
*/

// cpp encapsulation & polymorphism

class Node
{ // encapsulation
private:
	int data;

public:
	void set_data(int a);
	int get_data(void);
}

template <typename T>
class Node
{ // compile time polymorphism (template, function overloading) + runtime polymorphism (virtual functions)
private:
	T data;

public:
	void set_data(T a);
	T get_data(void);
}

// allocate dynamic memory in cpp
Node *n = new Node[10];
delete[] n;

// copy constructor
class Node
{
private:
	int data;

public:
	Node() : {};
	Node(const Node &node) : data(node.data){}; // Node n1; Node n2(n1);

	operator=(const Node &other) { data = other.data; } // Node n1 = n2;

	void set_data(int a);
	int get_data(void);
}

// type casting: static_cast, dynamic_cast, const_cast & reintepret_cast
void *ptr = new Node();
Node *n = dynamic_cast<Node *>(ptr);

// cpp
vector<int> nums{1, 2, 3}; // c++11
vector nums{1, 2, 3};      // c++17

// Design patterns: singleton, state, builder, observer
enum NodeStates_e {
	start,
	run,
	end
}

class NodeState
{
	prviate : NodeState_e state;
	NodeState curr;

public:
	void set_state();
	NodeState *get_state()
	{
		switch (state) {
		case start:
			if (!curr) return new NodeStartState() return curr;
		}
	}
}

class NodeStartState : NodeState
{
}

// cpp: multi threading
int thread_func(void *arg)
{
	while (1) {
		print("", );
		sleep(2);
	}
}

int data = 5;
std::thread t1(thread_func, *data);
std::thread t2(thread_func, *data);
t1.join();
t2.join();

// cpp networking protocols: tcp/ip, http, sip
