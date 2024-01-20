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

/* Time complexity: O(n^3) cubic */
int _01_brute_force(string s)
{
	auto is_uniq = [](string s, int b, int e) -> bool {
		vector m(128, 0);
		for (int k = b; k <= e; k++) {
			if (m[s[k]]++) return false;
		}
		return true;
	};

	size_t n = s.size();
	int d = 0;
	for (int b = 0; b < n; b++)
		for (int e = b; e < n; e++)
			if (is_uniq(s, b, e)) d = max(d, e - b + 1);
	return d;
}

/* Time complexity: O(n^2) square */
int _02_sliding_window(string s)
{
	size_t n = s.size();
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

/* Time complexity: O(n) linear */
int _03_optmized_sliding_window(string s)
{
	size_t n = s.size();
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

/* Time complexity: O(n) linear */
int _04_counter_sliding_window(string s)
{
	vector<int> m(128, 0);
	int c = 0, b = 0, e = 0, d = 0;
	while (e < s.size()) {
		if (m[s[e++]]++) c++;
		while (c)
			if (m[s[b++]]-- > 1) c--;
		d = max(d, e - b);
	}
	return d;
}

typedef std::function<int(std::string)> func_t;

void test_impl(vector<string> ip, vector<int> op, func_t impl)
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

int main(int ac, char **av)
{
	vector<string> ip{"", "abcabcbb", "bbbbb", "pwwkew"};
	vector<int> op{0, 3, 1, 3};
	vector<func_t> impls{
	    _01_brute_force,
	    _02_sliding_window,
	    _03_optmized_sliding_window,
	    _04_counter_sliding_window,
	};

	for (auto &impl : impls) test_impl(ip, op, impl);
	return 0;
}
