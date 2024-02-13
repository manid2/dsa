// global variable int
// 2 threads checking global variables & print Odd, Even

int num = 0; // initial value

pthread_cond_variable_t cv;
pthread_mutex_t mx;
pthread_lock_t lock;

void* print_odd(void*) {
	pthread_lock_lock(lock, mx);
	while(pthread_cond_wait()) {
		if (num % 2 == 0) continue; // if even then wait
		printf("%d\n", num++);
		pthread_cond_notify();
	}
	pthread_lock_unlock(lock, mx);
}

void* print_even(void*) {
	pthread_lock_lock(mx);
	while(pthread_cond_wait() && num) {
		if (num % 2 != 0) continue; // if odd then wait
		printf("%d\n", num++);
		pthread_cond_notify();
	}
	pthread_lock_unlock(mx);
}

// why condition variable is used?
while(!condition) { // uses cpu
	sleep (1);
}
// do some task


int main()
{
	pthread_t t1, t2;
	t1 = pthread_create(print_odd, NULL);
	t2 = pthread_create(print_even, NULL);
	t1.join();
}

// output
// 0 - t2 print_even
// 1 - t1 print_odd
// 2 - t2 print_even
// 3 - t1 print_odd
// 4 - t2 print_even

// WAP delete middle node of single linked list

typedef struct _node {
	int data;
	struct _node *next;
} Node

// odd:  1 -> 2 -> 3 -> 4 -> 5, delete 3
// even: 1 -> 2 -> 3 -> 4, delete 2
Node* delete_mid_node(Node *head)
{
	Node *temp = head;
	Node *fast = temp, *slow = temp;
	Node *prev = NULL;

	if (!temp) return NULL;
	if (!temp->next) { free(temp); return NULL;}

	while(fast->next && fast->next->next) {
		fast = fast->next->next;
		prev = slow;
		slow = slow->next;
	}
	prev->next = slow->next;
	free(slow);
	return head;
}

int main()
{
	Node *list = insert_list(1);
	list = delete_mid_node(list); // list is NULL
	return 0;
}
