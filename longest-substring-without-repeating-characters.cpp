#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/* Refer
 * https://www.enjoyalgorithms.com/blog/longest-substring-without-repeating-characters
 */

// optimizing sliding window Approach
int lengthOfLongestSubstring(string str)
{
	int n = str.size();
	if (n == 0)
		return 0;
	bool visited[256] = {};
	int maxLength = 0;
	int i = 0, j = 0;
	while (i < n && j < n)
	{
		if (visited[str[j]] == false)
		{
			visited[str[j]] = true;
			j = j + 1;
			maxLength = max(maxLength, j - i);
		}
		else
		{
			visited[str[i]] = false;
			i = i + 1;
		}
	}
	return maxLength;
}

int main(int ac, char **av)
{
	// Your code goes here;
	string s = "Hello";
	cout << lengthOfLongestSubstring(s) << endl;
	return 0;
}
