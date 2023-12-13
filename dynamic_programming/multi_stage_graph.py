from graphs import DirectedMatrixGraph


MAX_WEIGHT = float('inf')


class MultiStageGraph(DirectedMatrixGraph):
    def __init__(self, stages, vertices, edges=None):
        self.stages = stages
        super().__init__(vertices, edges)

    def get_shortest_path(self):
        """
        Get shortest path using forward approach.

        This is done in two steps:

        1. Find the minimum cost of each vertex and store it in cost table.
           This is filling the table for dynamic programming tabulation method
           in backwards direction.
        2. Select the vertices for path table from the minimum cost table.
           This is dynamic programming decision making in forward direction to
           solve the problem.
        """

        # Find the cost of each vertex from sink to source
        cost = [0] * self.vertices
        d = [0] * self.vertices
        for i in reversed(range(self.vertices - 1)):
            min_cost = MAX_WEIGHT
            for j in range(i + 1, self.vertices):
                if self.no_edge(i, j):
                    continue

                new_cost = self.edges[i][j] + cost[j]
                if new_cost < min_cost:
                    min_cost = new_cost
                    d[i] = j
            cost[i] = min_cost

        # Find the path from source to sink (forward)
        path = [0] * self.stages
        for i in range(1, self.stages - 1):
            path[i] = d[path[i - 1]]
        path[self.stages - 1] = self.vertices - 1
        return path, cost[0]
