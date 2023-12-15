import math


class MatrixChainMultiplication:
    """
    Minimum cost matrix chain multiplication using dynamic programming
    tabulation algorithm.

    Refer:

    * `4.3.1 Matrix Chain Multiplication (Program) - DP | Abdul Bari <yt1>`_

    .. _yt1: https://youtu.be/eKkXU3uu2zk?si=oEHMG0xYIGVZPEQZ
    """

    def __init__(self, dimensions):
        self.p = dimensions
        self.n = len(self.p)
        self.m = [[0] * self.n for i in range(self.n)]
        self.s = [[0] * self.n for i in range(self.n)]
        self._calc()
        self.a = self._paren(1, self.n - 1)

    def _get_q(self, i, j, k):
        qm = self.m[i][k] + self.m[k + 1][j]
        qp = self.p[i - 1] * self.p[k] * self.p[j]
        return qm + qp

    def _calc_min(self, i, j):
        minimum = math.inf
        for k in range(i, j):
            q = self._get_q(i, j, k)
            if q < minimum:
                minimum = q
                self.s[i][j] = k
        self.m[i][j] = minimum

    def _calc(self):
        for d in range(1, self.n - 1):
            for i in range(1, self.n - d):
                j = i + d
                self._calc_min(i, j)
        print(f"{self.s}")
        print(f"{self.m}")

    def _paren(self, i, j):
        """
        In-order traversal of solution matrix tree to generate parenthesis
        """

        a = ""
        if i == j:
            a += f"A{i}"
        else:
            a += "("
            a += self._paren(i, self.s[i][j])
            a += self._paren(self.s[i][j] + 1, j)
            a += ")"
        return a

    def get(self):
        return self.m[1][self.n - 1], self.a
