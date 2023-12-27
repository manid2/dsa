import pytest

from graphs import MAX_WEIGHT
from graphs import DirectedMatrixGraph, DirectedListGraph
from graphs import NegativeCycleError
from ds import KnapsackItem
from binary_trees import BinaryNode, BinarySearchTree

import dynamic_programming as dp


def test_dynamic_programming_fibonacci():
    exp_res = {5: 3, 10: 34}

    fm = dp.DpMemFibonacci()
    assert fm.get(5) == exp_res[5]
    assert fm.get(10) == exp_res[10]

    ft = dp.DpTabFibonacci()
    assert ft.get(5) == exp_res[5]
    assert ft.get(10) == exp_res[10]


def test_dynamic_programming_multi_stage_graph():
    exp_res = ([0, 1, 5, 7], 9)

    g = dp.MultiStageGraph(4, 8)
    # stage 0: vertex 0 (source)
    g.add_edge(0, 1, 2)
    g.add_edge(0, 2, 1)
    g.add_edge(0, 3, 3)
    # stage 1
    g.add_edge(1, 4, 2)
    g.add_edge(1, 5, 3)
    g.add_edge(2, 4, 6)
    g.add_edge(2, 5, 7)
    g.add_edge(3, 4, 6)
    g.add_edge(3, 5, 8)
    g.add_edge(3, 6, 9)
    # stage 2
    g.add_edge(4, 7, 6)
    g.add_edge(5, 7, 4)
    g.add_edge(6, 7, 5)
    # stage 3: vertex 7 (sink)
    assert g.get_shortest_path() == exp_res


def test_dynamic_programming_floyd_warshall():
    exp_res = [[0, 3, 5, 6],
               [5, 0, 2, 3],
               [3, 6, 0, 1],
               [2, 5, 7, 0]]

    x = MAX_WEIGHT
    g = DirectedMatrixGraph(4)
    g.add_edges([[0, 3, x, 7],
                 [8, 0, 2, x],
                 [5, x, 0, 1],
                 [2, x, x, 0]])
    e = dp.floyd_warshall(g)
    assert e == exp_res


class TestDynamicProgrammingMatrixChainMultiplication:
    exp_io = {(30, '(((A1A2)A3)A4)'): [1, 2, 3, 4, 3],
              (0, 'A1'): [10, 20],
              (722, '(A1A2)'): [19, 2, 19]}

    def test_matrix_chain_multiplication(self):
        for exp_res, li in self.exp_io.items():
            mcm = dp.MatrixChainMultiplication(li)
            assert mcm.get() == exp_res


class TestDynamicProgrammingBellamanFord:
    ip1 = [[2, 1, -10], [3, 2, 3], [0, 3, 5], [0, 1, 4]]
    ip2 = list(ip1)
    ip2.append([1, 3, 5])

    def test_bellman_ford(self):
        exp_res = [0, -2, 8, 5]
        g = DirectedListGraph(4, self.ip1)
        bf = dp.BellmanFord(g)
        assert bf.get() == exp_res

    def test_bellman_ford_negative_cycle(self):
        with pytest.raises(NegativeCycleError, match="Negative cycle found"):
            g = DirectedListGraph(4, self.ip2)
            dp.BellmanFord(g)


class TestDynamicProgrammingKnapsack:
    def test_zero_one_knapsack(self):
        exp_res = (8, [0, 1, 0, 1])
        items = [KnapsackItem(p, w)
                 for p, w in [(1, 2),
                              (2, 3),
                              (5, 4),
                              (6, 5)]]
        capacity = 8
        ks = dp.ZeroOneKnapsack(items, capacity)
        assert ks.get() == exp_res


class TestDynamicProgrammingOptimalBST:
    def test_optimal_bst(self):
        keys = [0, 10, 20, 30, 40]
        success = [0, 3, 3, 1, 1]
        unsuccess = [2, 3, 1, 1, 1]

        root = BinaryNode(keys[2])
        root.left = BinaryNode(keys[1])
        root.right = BinaryNode(keys[3])
        root.right.right = BinaryNode(keys[4])

        bst = BinarySearchTree(root)

        exp_res = (2, bst)
        items = [dp.OptimalBSTItem(k, p, q)
                 for k, p, q in zip(keys, success, unsuccess)]
        ob = dp.OptimalBST(items)
        assert ob.get() == exp_res


class TestDynamicProgrammingTravellingSalesman:
    def test_travelling_salesman(self):
        source = 0
        vertices = 4

        exp_res_1 = (50, 't')
        edges_1 = [[0, 20, 42, 25],
                   [20, 0, 30, 34],
                   [42, 30, 0, 10],
                   [25, 34, 10, 0]]

        _io = [(edges_1, exp_res_1)]

        for edges, exp_res in _io:
            g = dp.TravellingSalesman(source, vertices, edges)
            assert g.get() == exp_res
