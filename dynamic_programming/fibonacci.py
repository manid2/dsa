#!/usr/bin/env python3

class DpMemFibonacci:
    """
    Dynamic programming memoization Nth Fibnoacci.

    Memoization is a top-down recursive approach the sequence array is filled
    when returning from recursion tree.

    Complexities:
    * Time: O(n)
    * Space: O(n)
    """

    def __init__(self):
        self.seq = [0, 1]

    def get(self, n):
        if n < 0:
            raise ValueError(f"Negative value {n} not supported!")
        else:
            return self.fibo(n)

    def fibo(self, n):
        if n <= len(self.seq):
            return self.seq[n - 1]
        else:
            t = self.fibo(n - 2) + self.fibo(n - 1)
            self.seq.append(t)
            return t


class DpTabFibonacci:
    """
    Dynamic programming tabulation Nth Fibnoacci.

    Tabulation is a bottom-up iterative approach the sequence array is filled
    when before going down recursion tree.

    Complexities:
    * Time: O(n)
    * Space: O(n)
    """

    def __init__(self):
        self.seq = [0, 1]

    def get(self, n):
        if n < 0:
            raise ValueError(f"Negative value {n} not supported!")
        else:
            return self.fibo(n)

    def fibo(self, n):
        if n <= len(self.seq):
            return self.seq[n - 1]
        else:
            for i in range(len(self.seq), n):
                self.seq.append(self.seq[i - 2] + self.seq[i - 1])
            return self.seq[n - 1]
