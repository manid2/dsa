/**
 * Longest Substring Without Repeating Characters
 * ==============================================
 *
 * Leetcode: [3. Longest Substring Without Repeating Characters][lc3]
 *
 * Given a string s, find the length of the longest substring without
 * repeating characters.
 *
 * Tags: #strings, #medium
 *
 * Example 1:
 *
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 *
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 *
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *
 * Notice that the answer must be a substring, "pwke" is a subsequence and not
 * a substring.
 *
 * Solution
 * --------
 *
 * Refer:
 *
 * [sliding window technique][lcdi1]
 * [Optimized sliding window solution][ea1]
 *
 * [lc3]: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * [lcdi1]: https://discuss.leetcode.com/topic/30941/here-is-a-10-line-template-that-can-solve-most-substring-problems
 * [ea1]: https://www.enjoyalgorithms.com/blog/longest-substring-without-repeating-characters
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

	virtual int maxLenUniqCharsSubstr(const string &str) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(n^3)
 * SC : O(1)
 */
class _01_brute_force : public _00_test
{
public:
	_01_brute_force()
	    : _00_test("Longest Substring Without Repeating Characters brute "
	               "force")
	{
	}

	int maxLenUniqCharsSubstr(const string &s) override
	{
		auto is_uniq = [](string s, int b, int e) -> bool {
			vector m(128, 0);
			for (int k = b; k <= e; k++) {
				if (m[s[k]]++) return false;
			}
			return true;
		};

		int n = static_cast<int>(s.size());
		int d = 0;
		for (int b = 0; b < n; b++)
			for (int e = b; e < n; e++)
				if (is_uniq(s, b, e)) d = max(d, e - b + 1);
		return d;
	}
};

/* TC : O(n^2)
 * SC : O(1)
 */
class _02_sliding_window : public _00_test
{
public:
	_02_sliding_window()
	    : _00_test("Longest Substring Without Repeating Characters "
	               "sliding window")
	{
	}

	int maxLenUniqCharsSubstr(const string &s) override
	{
		int n = static_cast<int>(s.size());
		int b = 0, e = 0, d = 0;
		while (b < n) {
			vector m(128, 0);
			e = b;
			while (e < n && !m[s[e]]) {
				d = max(d, e - b + 1);
				m[s[e++]]++;
			}
			b++;
		}
		return d;
	}
};

/* TC : O(n)
 * SC : O(1)
 */
class _03_optmized_sliding_window : public _00_test
{
public:
	_03_optmized_sliding_window()
	    : _00_test("Longest Substring Without Repeating Characters "
	               "optimized sliding window")
	{
	}

	int maxLenUniqCharsSubstr(const string &s) override
	{
		int n = static_cast<int>(s.size());
		vector m(128, 0);
		int b = 0, e = 0, d = 0;
		while (b < n && e < n) {
			if (!m[s[e]]++) {
				e++;
				d = max(d, e - b);
			} else
				m[s[b++]] = 0;
		}
		return d;
	}
};

/* TC : O(n)
 * SC : O(1)
 */
class _04_counter_sliding_window : public _00_test
{
public:
	_04_counter_sliding_window()
	    : _00_test("Longest Substring Without Repeating Characters "
	               "counter sliding window")
	{
	}

	int maxLenUniqCharsSubstr(const string &s) override
	{
		vector<int> m(128, 0);
		int c = 0, b = 0, e = 0, d = 0;
		while (e < static_cast<int>(s.size())) {
			if (m[s[e++]]++) c++;
			while (c)
				if (m[s[b++]]-- > 1) c--;
			d = max(d, e - b);
		}
		return d;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
void test_impl(const vector<string> &ip, const vector<int> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		int t = f->maxLenUniqCharsSubstr(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << op[i] << ", actual " << t
			     << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: str = " << ip[i]
			     << "  output: maxLen = " << t << "\n";
	}
}

int main(int, char **)
{
	vector<string> ip{"", "abcabcbb", "bbbbb", "pwwkew"};

	vector<int> op{0, 3, 1, 3};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_brute_force>(),
	    make_shared<_02_sliding_window>(),
	    make_shared<_03_optmized_sliding_window>(),
	    make_shared<_04_counter_sliding_window>(),
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
