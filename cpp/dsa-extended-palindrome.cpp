// c++ code to get extended palindrome

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

bool isp(string &s)
{
	string p = s;
	reverse(p.begin(), p.end());
	return (s == p);
}

bool isl(vector<string> &l)
{
	vector<string> r = l;
	reverse(r.begin(), r.end());
	return (r == l);
}

bool iscp(string s, int d)
{
	size_t cs = s.size() / d;
	size_t c = 0;
	vector<string> l;
	for (size_t i = 0; i < cs; i++, c += d) {
		string p(s.begin() + c, s.begin() + c + d);
		l.push_back(p);
	}
	return isl(l);
}

int solution(string &s)
{
	if (isp(s)) return 1;

	// get prime divisor of |s| or 1
	size_t d = 1;
	for (size_t i = 2; i < s.size(); i++) {
		if ((s.size() % i) == 0) {
			d = i;
			break;
		}
	}

	if (iscp(s, d)) return d;

	return -1;
}

// driver code
int main(int v, char **a)
{
	vector<string> vl = {"radar", "abcxyzabc", "microsoft"};
	for (auto a : vl) {
		cout << "s=" << a << "\n\tr=" << solution(a) << endl;
	}
	return 0;
}
