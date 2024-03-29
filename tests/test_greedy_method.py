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


class TestGreedyMethodHuffmanCoding:
    def test_huffman_coding(self):
        exp_res = {'f': '0',
                   'c': '100',
                   'd': '101',
                   'a': '1100',
                   'b': '1101',
                   'e': '111'}

        chars_freqs = {'a': 5,
                       'b': 9,
                       'c': 12,
                       'd': 13,
                       'e': 16,
                       'f': 45}

        hc = gm.HuffmanCoding(chars_freqs)
        assert hc.compress() == exp_res


class TestGreedyMethodOptimalMergePattern:
    exp_io = {14: [2, 3, 4],
              205: [5, 10, 20, 30, 30],
              96: [8, 8, 8, 8, 8]}

    def test_optimal_merge_pq(self):
        for exp_res, li in self.exp_io.items():
            opm = gm.OptimalMergePatternWithPQ(li)
            assert opm.get() == exp_res

    def test_optimal_merge_list(self):
        for exp_res, li in self.exp_io.items():
            opm = gm.OptimalMergePatternWithList(li)
            assert opm.get() == exp_res
