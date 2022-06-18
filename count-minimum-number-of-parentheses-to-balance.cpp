// C++ code to get the minimum number of parentheses to be added to make it
// valid
// Refer:
// https://www.geeksforgeeks.org/minimum-number-of-parentheses-to-be-added-to-make-it-valid/

int solution(string &s) {
    if (s.empty())
        return 0;

    int b = 0, r = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        b += (s[i] == '(' ? 1 : -1);
        if (b == -1) {
            r += 1;
            b += 1;
        }
    }

    return b + r;
}
