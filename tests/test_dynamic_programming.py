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
