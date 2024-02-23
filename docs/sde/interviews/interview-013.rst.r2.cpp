// Oracle round 2

#include <stdio.h>

// 5, 6, 7, 8, 1, 2, 3

int find_num(int arr[], int size, int num)
{
	// TC: O(n)
	int p = 0;
	for (int i = 0; i < size - 1; i++) {
		if (num > arr[i + 1]) {
			p = i;
			break;
		}
	}

	// TC: O(log n)
	int b = 0, e = p;
	int mid = (e - b) / 2;
	while (b < e) {
		if (num == arr[mid])
			return mid;
		else if (num > arr[mid]) {
			b = mid;
		} else if (num < arr[mid]) {
			e = mid;
		}
		mid = (e - b) / 2;
	}
}

// 5, 6, 7, 8, 1, 2, 3
// num: 2

int find_num(int arr[], int size, int num)
{
	// TC: O(log n)
	int b = 0, e = 0, p = 0;
	int mid = (e - b) / 2;

	// 5, 6, 7, 8, 1, 2, 3
	while (b < e) {
		if (num == arr[mid])
			return mid;
		else if (num > arr[mid]) {
			if (arr[b] < num) e = mid;
		} else if (num < arr[mid]) {
			if (arr[e] > num) b = mid;
		}
		mid = (e - b) / 2;
	}
}

int main()
{
	printf("Hello World");

	return 0;
}
