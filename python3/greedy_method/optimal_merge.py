from abc import ABC, abstractmethod
from queue import PriorityQueue


class OptimalMergePattern(ABC):
    """
    Optimal merge pattern algorithm to optimize cost of merging sorted
    lists/files.

    Refer:

    * Optimal Merge Pattern | github.com/TheAlgorithms/Python/
    * `Optimal File Merge Patterns | GeeksForGeeks <gfg1>`_

    .. _gfg1: https://www.geeksforgeeks.org/optimal-file-merge-patterns/
    """

    def __init__(self, sorted_lists):
        self.sorted_lists = sorted_lists
        self.min_cost = 0
        self._calc()

    @abstractmethod
    def _calc(self):
        pass

    def get(self):
        return self.min_cost


class OptimalMergePatternWithList(OptimalMergePattern):
    def _calc(self):
        while len(self.sorted_lists) > 1:
            temp = 0
            # Consider two lists with minimum cost to be merged
            for _ in range(2):
                min_index = self.sorted_lists.index(min(self.sorted_lists))
                temp += self.sorted_lists[min_index]
                self.sorted_lists.pop(min_index)
            self.sorted_lists.append(temp)
            self.min_cost += temp


class OptimalMergePatternWithPQ(OptimalMergePattern):
    def _calc(self):
        pq = PriorityQueue()
        for li in self.sorted_lists:
            pq.put(li)

        while pq.qsize() > 1:
            # Consider two files with minimum cost to be merged
            temp = pq.get() + pq.get()
            pq.put(temp)
            self.min_cost += temp
