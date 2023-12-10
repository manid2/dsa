class KruskalsMST:
    def find_subtree(self, parent, i):
        """Finds the root node of a subtree containing node `i`"""
        if parent[i] == i:
            return i
        return self.find_subtree(parent, parent[i])

    def connect_subtrees(self, parent, subtree_sizes, x, y):
        """Connects subtrees containing nodes `x` and `y`"""
        xroot = self.find_subtree(parent, x)
        yroot = self.find_subtree(parent, y)
        if subtree_sizes[xroot] < subtree_sizes[yroot]:
            parent[xroot] = yroot
        elif subtree_sizes[xroot] > subtree_sizes[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            subtree_sizes[xroot] += 1

    def kruskals_mst(self, graph):
        """
        Kruskal's algorithm to find the Minimum Spanning Tree (MST)

        Refer:

        * `Kruskal's algorithm | stackabuse <sa1>`_

        # noqa: E501
        .. _sa1: https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/minimum-spanning-trees-kruskals-algorithm/
        """

        # Sort edges by their weight
        graph.edges = sorted(graph.edges, key=lambda item: item[2])

        parent = list(range(graph.vertices))
        subtree_sizes = [0] * graph.vertices

        result = []
        e = i = min_cost = 0

        while e < (graph.vertices - 1):
            u, v, w = graph.edges[i]
            i = i + 1

            x = self.find_subtree(parent, u)
            y = self.find_subtree(parent, v)

            if x != y:
                e = e + 1
                result.append([u, v, w])
                min_cost += w
                self.connect_subtrees(parent, subtree_sizes, x, y)
        return result, min_cost
