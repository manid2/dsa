import pytest

from greedy_method import dijkstras

def test_greedy_method_dijsktras():
    exp_res = {0: 0, 1: 4, 2: 4, 3: 3, 4: 5}

    g = dijkstras.Graph(5)
    g.add_edge(0, 1, 4)
    g.add_edge(0, 3, 3)
    g.add_edge(0, 4, 5)
    g.add_edge(1, 2, 2)
    g.add_edge(2, 3, 1)
    start = 0
    res = g.dijkstras_path(start)
    assert res == exp_res
