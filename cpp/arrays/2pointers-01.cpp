#include <bits/stdc++.h>

using namespace std;

// Variations of Two pointers techniques - 01

// Move all 0 to right / end of array in place with same order for other
// elements

void move0toEnd()
{
	int A[] = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	int n = sizeof(A) / sizeof(A[0]);
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] != 0) {
			swap(A[j++], A[i]); // Partitioning the array
		}
	}

	for (int i = 0; i < n; i++) {
		cout << A[i] << " "; // Print the array
	}
}

// Move all 0 to left / begin of array in place with same order for other
// elements

void move0toBegin()
{
	int A[] = {5, 6, 0, 4, 6, 0, 9, 0, 8};
	int n = sizeof(A) / sizeof(A[0]);
	int j = n - 1;
	for (int i = n - 1; i >= 0; i--) {
		if (A[i] != 0) {
			swap(A[j--], A[i]); // Partitioning the array
		}
	}

	for (int i = 0; i < n; i++) {
		cout << A[i] << " "; // Print the array
	}
}

// Remove repeated / duplicates in sorted array

void removeDuplicatesSorted()
{
	int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 5};
	int n = sizeof(arr) / sizeof(arr[0]);

	if (n == 0 || n == 1) return;

	// To store index of next unique element
	int j = 0;

	// Doing same as done in Method 1
	// Just maintaining another updated index i.e. j
	for (int i = 0; i < n - 1; i++)
		if (arr[i] != arr[i + 1]) arr[j++] = arr[i];

	arr[j++] = arr[n - 1];
}

int main(int, char **)
{
	cout << "executed " << 1 << " implementations"
	     << " with " << 1 << " tests." << std::endl;
	return 0;
}
