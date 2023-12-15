from graphs import UndirectedMatrixGraph, UndirectedListGraph
from ds import KnapsackItem

import greedy_method as gm


def _add_edges(g):
    g.add_edge(0, 1, 4)
    g.add_edge(0, 3, 3)
    g.add_edge(0, 4, 5)
    g.add_edge(1, 2, 2)
    g.add_edge(2, 3, 1)
    return g


class TestGreedyMethodMGraphs:
    g = _add_edges(UndirectedMatrixGraph(5))

    def test_dijsktras_path(self):
        exp_res = {0: 0, 1: 4, 2: 4, 3: 3, 4: 5}
        start = 0
        res = gm.dijkstras_path(start, self.g)
        assert res == exp_res

    def test_prims_mst(self):
        exp_res = 11
        _, res = gm.prims_mst(self.g)
        assert res == exp_res


class TestGreedyMethodLGraphs:
    g = _add_edges(UndirectedListGraph(5))

    def test_kruskals_mst(self):
        exp_res = 11
        k = gm.KruskalsMST()
        _, res = k.kruskals_mst(self.g)
        assert res == exp_res

class TestGreedyMethodKnapsack:
    def test_fractional_knapsack(self):
        exp_res = 240.0
        items = [KnapsackItem(p, w)
                 for p, w in [(60, 10),
                              (100, 20),
                              (120, 30)]]
        capacity = 50
        ks = gm.FractionalKnapsack(items, capacity)
        assert ks.get() == exp_res
