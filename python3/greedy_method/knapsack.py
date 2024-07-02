from ds import Knapsack


class FractionalKnapsack(Knapsack):
    def get(self):
        # sort items in decreasing order of profit per unit weight ratios
        self.items.sort(key=lambda x: (x.profit / x.weight), reverse=True)
        result = 0.0
        remain = self.capacity
        for item in self.items:
            if item.weight <= remain:
                remain -= item.weight
                result += item.profit
            else:
                result += item.profit * remain / item.weight
                break
        return result
