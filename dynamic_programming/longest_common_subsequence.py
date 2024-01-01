class LongestCommonSubsequence:
    """
    Longest Common Subsequence (LCS)

    This problem is solved using dynamic programming tabulation method.

    Complexities:
    Given m is length of string 1 and n is length string 2.
    * Time: O(m*n)
    * Space: O(m*n)

    Tags: #medium

    Refer:

    * `Traveling Salesman Problem (DP) | Abdul Bari <abyt1>`_
    * `Traveling Salesman Problem (DP) | programiz.com <pgz1>`_

    .. _abyt1: https://youtu.be/sSno9rV8Rhg?si=s36ywvtq5UDV141P
    .. _pgz1: https://www.programiz.com/dsa/longest-common-subsequence
    """

    def __init__(self, str1, str2):
        self.s1 = str1
        self.s2 = str2
        self.m = len(self.s1)
        self.n = len(self.s2)
        self.tab = []
        self.len = self._get_len()
        self.seq = self._get_seq()

    def _get_len(self):
        m1 = self.m + 1
        n1 = self.n + 1
        self.tab = [[0 for _ in range(n1)]
                    for _ in range(m1)]
        for i in range(m1):
            for j in range(n1):
                if i == 0 or j == 0:
                    self.tab[i][j] = 0
                elif self.s1[i - 1] == self.s2[j - 1]:
                    self.tab[i][j] = self.tab[i - 1][j - 1] + 1
                else:
                    self.tab[i][j] = max(self.tab[i - 1][j],
                                         self.tab[i][j - 1])
        return self.tab[self.m][self.n]

    def _get_seq(self):
        k = self.len
        seq = [""] * k
        i = self.m
        j = self.n
        while i and j:
            if self.s1[i - 1] == self.s2[j - 1]:
                seq[k - 1] = self.s1[i - 1]
                i -= 1
                j -= 1
                k -= 1
            elif self.tab[i - 1][j] > self.tab[i][j - 1]:
                i -= 1
            else:
                j -= 1
        return ''.join(seq)

    def get(self):
        return self.len, self.seq
