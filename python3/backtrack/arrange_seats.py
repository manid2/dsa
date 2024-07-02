from .backtrack import Backtrack


class ArrangeSeats(Backtrack):
    """
    Find all possible seat arrangements for 2 Boys and 1 Girl.
    """

    OPTIONS = {"B1", "B2", "G1"}

    def _get_candidates(self):
        # constraint: girl cannot sit in the middle
        if len(self.state) > 1 and self.state[1] == "G1":
            return []
        return list(self.OPTIONS.difference(set(self.state)))
