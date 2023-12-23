from ds import Knapsack


class ZeroOneKnapsack(Knapsack):
    """
    0/1 Knapsack solution using dynamic programming tabulation method.

    Refer:

    * `0/1 Knapsack (DP) program | Abdul Bari <abyt1>`_

    .. _abyt1: https://youtu.be/zRza99HPvkQ?si=Eh1Y2uaDgF6RkHmu
    """

    def __init__(self, items, capacity):
        super().__init__(items, capacity)
        self.k = [[0 for w in range(self.capacity + 1)]
                  for i in range(self.n_items + 1)]
        self.max_weight = self._get_max_weight()
        self.included_items = self._get_included_items()

    def _get_max_weight(self):
        for i in range(self.n_items + 1):
            for w in range(self.capacity + 1):
                if i == 0 or w == 0:
                    self.k[i][w] = 0
                elif self.items[i - 1].weight <= w:
                    _p = self.items[i - 1].profit
                    _w = self.k[i - 1][w - self.items[i - 1].weight]
                    self.k[i][w] = max(_p + _w, self.k[i - 1][w])
                else:
                    self.k[i][w] = self.k[i - 1][w]
        return self.k[self.n_items][self.capacity]

    def _get_included_items(self):
        included_items = [0] * self.n_items
        i = self.n_items
        j = self.capacity
        while i > 0 and j > 0:
            if self.k[i][j] != self.k[i - 1][j]:
                included_items[i - 1] = 1
                j -= self.items[i - 1].weight
            i -= 1
        return included_items

    def get(self):
        return self.max_weight, self.included_items
