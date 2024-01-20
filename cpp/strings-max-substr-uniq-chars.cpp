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
 * Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
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

/* Use optimized sliding window */
int lengthOfLongestSubstring(string s)
{
	size_t n = s.size();
	vector m(128, 0);
	int b = 0, e = 0, d = 0;
	while (b < n && e < n) {
		if (!m[s[e]]++) {
			e++;
			d = max(d, e - b);
		}
		else
			m[s[b++]] = 0;
	}
	return d;
}

int main(int ac, char **av)
{
	vector<string> ip{"", "abcabcbb", "bbbbb", "pwwkew"};
	vector<int> op{0, 3, 1, 3};

	for (size_t i = 0; i < ip.size(); i++) {
		int t = lengthOfLongestSubstring(ip[i]);
		if (op[i] != t) {
			cerr << "test failed: "
			        "expected " << op[i] << ", "
			        "actual " << t << endl;
			return 1;
		}
		cout << t << endl;
	}
	return 0;
}
