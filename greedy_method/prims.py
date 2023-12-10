#!/usr/bin/env python3


MAX_WEIGHT = float('inf')


class Graph:
    """This graph is represented using adjacency matrix"""

    def __init__(self, vertices=0, edges=None):
        self.vertices = vertices if vertices else len(edges)

        if edges and self.is_valid_edges(edges):
            self.edges = edges
        else:
            self.edges = self.get_init_edges()

    def get_init_edges(self):
        return [[0 for column in range(self.vertices)]
                for row in range(self.vertices)]

    def is_valid_node(self, a):
        return -1 < a < self.vertices

    def is_valid_edges(self, edges):
        return (self.vertices == len(edges) and
                self.vertices == len(edges[0]))

    def add_edge(self, a, b, weight):
        """Add an edge to undirected weighted graph"""

        if self.is_valid_node(a) and self.is_valid_node(b):
            self.edges[a][b] = self.edges[b][a] = weight
        else:
            raise ValueError(f"Invalid nodes {a}, {b}, " +
                             "a valid node is in range " +
                             f"[0, {self.vertices - 1}]")

    def add_edges(self, edges):
        """Add all edges in the form of adjacency matrix to the graph"""

        if self.is_valid_edges(edges):
            self.edges = edges
        else:
            raise ValueError("Invalid adjacency matrix, " +
                             "a valid matrix must be " +
                             f"{self.vertices} x {self.vertices}")

    def print(self):
        for i in range(self.vertices):
            for j in range(0 + i, self.vertices):
                if self.edges[i][j]:
                    print(f"{i}-{j}: {self.edges[i][j]}")

    def prims_mst(self):
        """
        Prim's algorithm to find the Minimum Spanning Tree (MST)

        Refer:

        * `Prim's algorithm | favtutor <fv1>`_

        .. _fv1: https://favtutor.com/blogs/prims-algorithm-python
        """

        # Keep a list of selected nodes to ensure they are not picked twice
        selected_nodes = [False for node in range(self.vertices)]

        # Result MST edges and min cost
        result = self.get_init_edges()
        min_cost = 0

        while False in selected_nodes:

            # Use infinite weight to select the initial minimum weight
            min_weight = MAX_WEIGHT
            a = b = 0

            for i in range(self.vertices):
                if not selected_nodes[i]:
                    continue

                # If a node (i) is selected then check if it has a minimum
                # cost path to another unselected node (j)
                for j in range(self.vertices):
                    if selected_nodes[j]:
                        continue

                    if not self.edges[i][j]:
                        continue

                    if self.edges[i][j] < min_weight:
                        min_weight = self.edges[i][j]
                        a, b = i, j

            if min_weight == MAX_WEIGHT:
                min_weight = 0

            selected_nodes[b] = True
            result[a][b] = result[b][a] = min_weight
            min_cost += min_weight

        return result, min_cost

# TODO: Add pytest and tox for automated tests


def solve():
    edges = [[0, 4, 0, 3, 5],
             [4, 0, 2, 0, 0],
             [0, 2, 0, 1, 0],
             [3, 0, 1, 0, 0],
             [5, 0, 0, 0, 0]]

    g = Graph(edges=edges)
    r, m = g.prims_mst()

    print("=== Prim's MST ===")
    res = Graph(edges=r)
    res.print()
    print(f"min cost: {m}")


solve()
