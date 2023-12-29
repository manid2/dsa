import math


class OptimalBSTItem:
    def __init__(self, key, success, unsuccess):
        self.key = key
        self.success = success
        self.unsuccess = unsuccess


class OptimalBST:
    """
    Optimal binary search tree (BST) using dynamic programming tabulation
    method

    Refer:

    * `Optimal BST (DP) | Abdul Bari <abyt1>`_
    * `Optimal BST (DP) | codecrucks <cc1>`_

    .. _abyt1: https://youtu.be/wAy6nDMPYAE?si=xjNrNveyvEtvGU_l
    .. _cc1: https://codecrucks.com/optimal-binary-search-tree-how-to-solve-using-dynamic-programming/ # noqa: E501
    """

    def __init__(self, items):
        self.k = [i.key for i in items]
        self.p = [i.success for i in items]
        self.q = [i.unsuccess for i in items]
        self.n = len(self.k) - 1  # ignore first dummy key
        self.w = self._get_init_table()
        self.c = self._get_init_table()
        self.r = self._get_init_table()
        self.m = self._calc()
        self.t = self._create_bst()

    def _get_init_table(self):
        n1 = self.n + 1
        return [[0 for _ in range(n1)]
                for _ in range(n1)]

    def _calc(self):
        n1 = self.n + 1

        for i in range(n1):
            self.w[i][i] = self.q[i]

        for d in range(1, n1):
            for i in range(0, (n1 - d)):
                j = i + d
                j1 = j + 1
                self.w[i][j] = self.w[i][j - 1] + self.p[j] + self.q[j]
                self.c[i][j] = math.inf
                for k in range(i, j1):
                    minimum = self.c[i][k - 1] + self.c[k][j] + self.w[i][j]
                    if minimum < self.c[i][j]:
                        self.c[i][j] = minimum
                        self.r[i][j] = k

        sum_pq = sum(self.p[1:] + self.q)
        min_cost = self.c[0][self.n] // sum_pq
        return min_cost

    def _create_bst(self):
        # TODO construct binary search tree from root table i.e. 'self.r[][]'
        return 't'

    def get(self):
        return self.m, self.t
