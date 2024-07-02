from abc import ABC, abstractmethod


class KnapsackItem:
    def __init__(self, profit, weight):
        self.profit = profit
        self.weight = weight


class Knapsack(ABC):
    def __init__(self, items, capacity):
        self.items = items
        self.capacity = capacity
        self.n_items = len(items)

    @abstractmethod
    def get(self):
        pass
