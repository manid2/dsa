#include <iostream>

using namespace std;

/* ===========================================================================
 * 1. Singleton pattern
 * ===========================================================================
 */

class Singleton
{
public:
	static Singleton &getInstance()
	{
		static Singleton obj;
		return obj;
	}

	//Singleton(const Singleton &&) = default;

	void setData(int d) { data = d; }
	int getData() { return data; }

private:
	int data;
};

class Test1
{
public:
	Singleton &obj;

	Test1() : obj(Singleton::getInstance()) {}

	void printData() { cout << "Test1: " << obj.getData() << endl; }
};

class Test2
{
public:
	Singleton &obj;

	Test2() : obj(Singleton::getInstance()) {}

	void printData() { cout << "Test2: " << obj.getData() << endl; }
};

int main()
{
	Test1 t1;
	Test2 t2;

	t1.obj.setData(5);

	t1.printData();
	t2.printData();

	t2.obj.setData(11);

	t1.printData();
	t2.printData();
	return 0;
}

/* ===========================================================================
 * 2. DSA - Arrays
 * ===========================================================================
 */
/*
Given an integer array, move all elements that are 0 to the left while
maintaining the order of other elements in the array. The array must be
modified in-place
 
You cannot use a simple chronological sort as elements other than zeros must
maintain their position.
*/

void rotateArray(vector<int> &a, int s, int e)
{
	while (e >= s) {
		a[e] = a[e - 1];
		e--;
	}
}

void move0toLeft(vector<int> &a)
{
	int i = 0, j = 0;
	for (; i < a.size(); i++) {
		if (a[i] == 0) {
			rotateArray(a, j, i);
			a[j++] = 0;
		}
	}
}

void printVec(const vector<int> &a)
{
	for (auto e : a) cout << e << ", ";
	cout << endl;
}

int main()
{
	vector<int> a{1, 10, 20, 0, 59, 63, 0, 88, 0};

	cout << "Before: ";
	printVec(a);

	move0toLeft(a);

	cout << "After: ";
	printVec(a);
	return 0;
}
