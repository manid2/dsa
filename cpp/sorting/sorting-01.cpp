/**
 * Sorting Algorithms - 01
 * =======================
 *
 * Implemented worst case TC O(n^2) sorting algorithms in this file.
 *
 * Refer:
 *
 * https://www.programiz.com/dsa/bubble-sort
 */

#include <bits/stdc++.h>

using namespace std;

/* TC : O(n^2)
 * SC : O(1)
 */
class _01_bubble_sort
{
public:
	void sort(vector<int> &nums)
	{
		// implement
	}

	void operator()(vector<int> &nums) { return this->sort(nums); }
};

class _02_selection_sort;
class _03_insertion_sort;

typedef std::function<int(vector<int> &)> func_t;

void test_impl(const vector<vector<int>> &ip, const vector<int> &op,
               func_t impl)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = impl(ip[i]);
		if (op[i] != t) {
			cerr << "test failed: expected " << op[i]
			     << ", actual " << t << endl;
			exit(1);
		}
		cout << t << endl;
	}
}

int main(int argc, char *argv[])
{
	vector<vector<int>> ip{
	    // add input
	};
	vector<int> op{190, 76, 102}; // check output

	vector<func_t> impls{
	    _01_bubble_sort(), _02_selection_sort(), _03_insertion_sort(),
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
