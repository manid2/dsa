/**
 * Pascal's triangle
 *
 * Refer
 *
 * https://www.geeksforgeeks.org/pascal-triangle/
 */

#include <bits/stdc++.h>

using namespace std;

// =================================================
// 1. Using Binomial Coefficients
// TC: O(n^3)
// SC: O(1)
// =================================================

int binomialCoeff(int n, int k);

// Function to print first
// n lines of Pascal's
// Triangle
void printPascal(int n)
{
	// Iterate through every line and
	// print entries in it
	for (int line = 0; line < n; line++) {
		// Every line has number of
		// integers equal to line
		// number
		for (int i = 0; i <= line; i++)
			cout << " " << binomialCoeff(line, i);
		cout << "\n";
	}
}

// See
// https://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/
// for details of this function
int binomialCoeff(int n, int k)
{
	int res = 1;
	if (k > n - k) k = n - k;
	for (int i = 0; i < k; ++i) {
		res *= (n - i);
		res /= (i + 1);
	}

	return res;
}

// =================================================
// 2. Using Dynamic Programming
// TC: O(n^2)
// SC: O(n^2)
// =================================================

void printPascal(int n)
{
	// An auxiliary array to store
	// generated pascal triangle values
	int arr[n][n];

	// Iterate through every line and
	// print integer(s) in it
	for (int line = 0; line < n; line++) {
		// Every line has number of integers
		// equal to line number
		for (int i = 0; i <= line; i++) {
			// First and last values in every row are 1
			if (line == i || i == 0) arr[line][i] = 1;

			// Other values are sum of values just
			// above and left of above
			else
				arr[line][i] =
				    arr[line - 1][i - 1] + arr[line - 1][i];
			cout << arr[line][i] << " ";
		}
		cout << "\n";
	}
}

// =================================================
// 3. Using Dynamic Programming space optimized
// TC: O(n^2)
// SC: O(1)
// =================================================

void printPascal(int n)
{
	// An auxiliary array to store
	// generated pascal triangle values
	int prev[n];

	// Iterate through every line and
	// print integer(s) in it
	for (int line = 0; line < n; line++) {
		// Every line has number of integers
		// equal to line number
		for (int i = 0; i <= line; i++) {
			int C = 1;
			if (line != i || i != 0) C = prev[i - 1] + prev[i];
			cout << C << " ";
		}
		cout << "\n";
	}
}

// =================================================
// 4. Using Dynamic Programming space optimized
// TC: O(n^2)
// SC: O(1)
// =================================================

void printPascal(int n)
{
	for (int line = 1; line <= n; line++) {
		int C = 1; // used to represent C(line, i)
		for (int i = 1; i <= line; i++) {

			// The first value in a line is always 1
			cout << C << " ";
			C = C * (line - i) / i;
		}
		cout << "\n";
	}
}

// =================================================
// Driver program
int main()
{
	//int n = 7;
	//printPascal(n);
	return 0;
}
