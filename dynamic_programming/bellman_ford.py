from graphs import MAX_WEIGHT, NegativeCycleError


class BellmanFord:
    """
    Bellman-Ford algorithm to find single source shortest path to all nodes.

    Refer:

    * `Bellman-Ford Algorithm | GFG <gfg1>`_

    .. _sa1: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
    """

    def __init__(self, graph, src=0):
        self.g = graph
        self.s = src
        self.d = [MAX_WEIGHT] * self.g.vertices
        self.d[self.s] = 0
        self._calc()

    def _relax_one(self, u, v, nd, nth):
        if self.d[u] != MAX_WEIGHT and nd < self.d[v]:
            if nth:
                raise NegativeCycleError
            self.d[v] = nd

    def _relax(self, nth):
        for u, v, w in self.g.edges:
            nd = self.d[u] + w
            self._relax_one(u, v, nd, nth)

    def _calc(self):
        for _ in range(self.g.vertices - 1):
            self._relax(False)
        self._relax(True)

    def get(self):
        return self.d
