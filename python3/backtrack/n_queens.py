from .backtrack import Backtrack


class NQueens(Backtrack):
    """
    Find valid solutions to place N queens in (N x N) chess board.
    """

    MIN_ITEMS = 4

    def _get_candidates(self):
        candidates = set(range(self.items))
        if not self.state:
            return candidates

        next_row = len(self.state)
        for row, col in enumerate(self.state):
            # remove col indices in previous rows i.e. state
            candidates.discard(col)
            # discard diagonal candidates to current position
            dist = next_row - row
            candidates.discard(col + dist)
            candidates.discard(col - dist)
        return candidates
