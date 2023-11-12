// C program to queue push & pop using array as queue

#include <stdio.h>

#define SIZE 5

void push(int);
void pop();

int queue[SIZE], front = -1, rear = -1;

int main(int a, char **v) {
	// push elements
	push (1);
	push (2);
	push (3);
	push (4);
	push (5);

	// elements in queue now: 5, 4, 3, 2, 1

	// pop elements
	pop ();
	pop ();

	// elements in queue now: 5, 4, 3
	return 0;
}

int push (int value) {
	if (rear == SIZE - 1)
		return -1;
	else {
		if (front == -1)
			front = 0;
		rear++;
		queue[rear] = value;
		return rear;
	}
	return 0;
}

int pop () {
	int ret = -1;
	if (front == -1)
		return ret;
	else {
		ret = front;
		queue[ret] = 0; // reset value here
		front++;
		if (front > rear)
			front = rear = -1;
	}
	return ret;
}
