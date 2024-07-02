from abc import ABC, abstractmethod


class Backtrack(ABC):
    """
    This is a generic backtrack algorithms interface.

    It provides a template to solve a problem using backtrack algorithm.

    Derived class need to provide:
    * MIN_ITEMS: minimum number of items to ensure backtrack is feasible.
    """

    MIN_ITEMS = 2

    def __init__(self, items):
        if items < self.MIN_ITEMS:
            raise ValueError(f"Requires minimum {items} items")
        self.items = items
        self.state = []
        self.solutions = []
        self._solve()

    @abstractmethod
    def _get_candidates(self):
        pass

    def get(self):
        return self.solutions

    def _is_valid_state(self):
        return len(self.state) == self.items

    def _solve(self):
        if self._is_valid_state():
            self.solutions.append(self.state.copy())
            # print (f"Valid state: {state}")
            # return if only one valid solution is required

        for candidate in self._get_candidates():
            self.state.append(candidate)
            self._solve()
            # printf(f"backtracking from: {state}")
            self.state.remove(candidate)
