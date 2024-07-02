from backtrack import ArrangeSeats, NQueens


class TestBacktrack:
    def test_arrange_seats(self):
        exp_res = [['B1', 'B2', 'G1'],
                   ['G1', 'B1', 'B2'],
                   ['G1', 'B2', 'B1'],
                   ['B2', 'B1', 'G1']]
        solutions = ArrangeSeats(3).get()
        for solution in solutions:
            assert solution in exp_res

    def test_n_queens(self):
        exp_res = [[1, 3, 0, 2],
                   [2, 0, 3, 1]]
        solutions = NQueens(4).get()
        for solution in solutions:
            assert solution in exp_res
