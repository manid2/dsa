from graphs import DirectedMatrixGraph, MAX_WEIGHT


class TravellingSalesman(DirectedMatrixGraph):
    """
    Travelling salesman problem

    Calculate minimum cost and the path from a source vertex visiting all
    other vertices exactly once and returning to the source vertex.

    This problem is solved using dynamic programming memoization method. This
    is slightly faster then brute force approach to generate all possible
    permutations of vertices and find minimum cost in O(n!) time.

    Complexities:
    * Time: O(2^n*n^2) where:
        - O(2^n*n) are maximum number of sub-problems.
        - O(n) time to solve each sub-problem.

    * Space: O(2^n*n^2), where n is number of Nodes/Cities here.

    Tags: #hard #exponential

    Refer:

    * `Traveling Salesman Problem (DP) | Abdul Bari <abyt1>`_
    * `Traveling Salesman Problem (DP) | favtutor.com <fv1>`_

    .. _abyt1: https://youtu.be/Q4zHb-Swzro?si=KRK3CIVFqXirYxTQ
    .. _fv1: https://favtutor.com/blogs/travelling-salesman-problem
    """

    def __init__(self, source, vertices, edges=None):
        self.source = source
        super().__init__(vertices, edges)
        self.memo = self._get_init_memo()
        self.visited_all = (1 << self.vertices) - 1
        self.min_cost = self._get_min_cost()
        self.min_path = self._get_min_path()

    def _get_init_memo(self):
        return [[-1 for _ in range(self.vertices)]
                for _ in range(2 ** self.vertices)]

    def _get_min_cost(self):
        return self._tsp(1, self.source)

    def _tsp(self, mask, vertex):
        if mask == self.visited_all:
            return self.edges[vertex][self.source]

        if self.memo[mask][vertex] != -1:
            return self.memo[mask][vertex]

        min_cost = MAX_WEIGHT
        for v in range(self.vertices):
            bv = 1 << v
            is_visited = mask & bv
            if is_visited:
                continue
            mask |= bv
            new_min = self.edges[vertex][v] + self._tsp(mask, v)
            min_cost = min(min_cost, new_min)
        self.memo[mask][vertex] = min_cost
        return min_cost

    def _get_min_path(self):
        return 't'

    def get(self):
        return self.min_cost, self.min_path
