/**
 * Sorting Algorithms - 01
 * =======================
 *
 * Sorting algorithms with worst case TC O(n^2).
 *
 * Refer:
 *
 * https://www.geeksforgeeks.org/bubble-sort-in-cpp/
 * https://www.programiz.com/dsa/bubble-sort
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual void sort(vector<int> &nums) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
class _01_bubble_sort : public _00_test
{
public:
	_01_bubble_sort() : _00_test("Bubble sort") {}

	void sort(vector<int> &nums) override
	{
		int n = static_cast<int>(nums.size());
		for (int i = 0; i < n - 1; i++) {
			bool swapped = false;
			for (int j = 0; j < n - i - 1; j++) {
				if (nums[j] > nums[j + 1]) {
					swap(nums[j], nums[j + 1]);
					swapped = true;
				}
			}
			if (!swapped) break;
		}
	}
};

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
class _02_selection_sort : public _00_test
{
public:
	_02_selection_sort() : _00_test("Selection sort") {}

	void sort(vector<int> &nums) override
	{
		int n = static_cast<int>(nums.size());
		for (int i = 0; i < n - 1; i++) {
			int m = i;
			for (int j = i + 1; j < n; j++)
				m = nums[j] < nums[m] ? j : m;
			swap(nums[i], nums[m]);
		}
	}
};

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
class _03_insertion_sort : public _00_test
{
public:
	_03_insertion_sort() : _00_test("Insertion sort") {}

	void sort(vector<int> &nums) override
	{
		int n = static_cast<int>(nums.size());
		for (int i = 1; i < n; i++) {
			int key = nums[i];
			int j = i - 1;

			while (j >= 0 && nums[j] > key) {
				nums[j + 1] = nums[j];
				j = j - 1;
			}
			nums[j + 1] = key;
		}
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
string _vec2str(vector<int> &vec)
{
	ostringstream oss;
	oss << "{";
	copy(vec.begin(), vec.end() - 1, ostream_iterator<int>(oss, ", "));
	oss << vec.back();
	oss << "}";
	return oss.str();
}

void test_impl(vector<vector<int>> &ip, vector<vector<int>> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		vector<int> t = ip[i];
		f->sort(t);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << _vec2str(op[i]) << ", actual "
			     << _vec2str(t) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: nums = " << _vec2str(ip[i])
			     << "  output: nums = " << _vec2str(t) << "\n";
	}
}

int main(int, char **)
{
	vector<vector<int>> ip{
	    {5, 1, 4, 2, 8},
	    {-2, 45, 0, 11, -9},
	};

	vector<vector<int>> op{
	    {1, 2, 4, 5, 8},
	    {-9, -2, 0, 11, 45},
	};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_bubble_sort>(),
	    make_shared<_02_selection_sort>(),
	    make_shared<_03_insertion_sort>(),
	};

	for (size_t i = 0; i < impls.size(); i++) {
		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "Testing implementation " << i + 1 << " "
			     << impls[i]->getName() << "\n";

		test_impl(ip, op, impls[i]);
	}

	cout << "Executed " << impls.size() << " implementations"
	     << " with " << ip.size() << " tests." << endl;
	return 0;
}
