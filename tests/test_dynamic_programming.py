import dynamic_programming as dp


def test_dynamic_programming_fibonacci():
    exp_res = {5: 3, 10: 34}

    fm = dp.DpMemFibonacci()
    assert fm.get(5) == exp_res[5]
    assert fm.get(10) == exp_res[10]

    ft = dp.DpTabFibonacci()
    assert ft.get(5) == exp_res[5]
    assert ft.get(10) == exp_res[10]

    # TODO: Add negative tests


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
