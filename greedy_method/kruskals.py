#!/usr/bin/env python3


class Graph:
    """This graph is represented using adjacency list"""

    def __init__(self, vertices=0, edges=[]):
        self.vertices = vertices
        self.edges = edges

    def is_valid_node(self, a):
        return (a > 0 and a < self.vertices)

    def add_edge(self, a, b, weight):
        """Add an edge to undirected weighted graph"""

        if self.is_valid_node(a) and self.is_valid_node(b):
            self.edges.append([a, b, weight])
        else:
            raise ValueError(f"Invalid nodes {a}, {b}, " +
                             "a valid node is in range " +
                             "[0, {}]".format(self.vertices - 1))

    def add_edges(self, edges):
        """Add all edges in the form of adjacency list to the graph"""
        self.edges = edges

    def print(self):
        for a, b, weight in self.edges:
            print("{0}-{1}: {2}".format(a, b, weight))

    # Finds the root node of a subtree containing node `i`
    def find_subtree(self, parent, i):
        if parent[i] == i:
            return i
        return self.find_subtree(parent, parent[i])

    # Connects subtrees containing nodes `x` and `y`
    def connect_subtrees(self, parent, subtree_sizes, x, y):
        xroot = self.find_subtree(parent, x)
        yroot = self.find_subtree(parent, y)
        if subtree_sizes[xroot] < subtree_sizes[yroot]:
            parent[xroot] = yroot
        elif subtree_sizes[xroot] > subtree_sizes[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            subtree_sizes[xroot] += 1

    def kruskals_mst(self):
        """
        Kruskal's algorithm to find the Minimum Spanning Tree (MST)

        Refer:

        * `Kruskal's algorithm | stackabuse <sa1>`_

        # noqa: E501
        .. _sa1: https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/minimum-spanning-trees-kruskals-algorithm/
        """

        # Sort edges by their weight
        self.edges = sorted(self.edges, key=lambda item: item[2])

        parent = list(range(self.vertices))
        subtree_sizes = [0] * self.vertices

        result = []
        e = i = min_cost = 0

        while e < (self.vertices - 1):
            u, v, w = self.edges[i]
            i = i + 1

            x = self.find_subtree(parent, u)
            y = self.find_subtree(parent, v)

            if x != y:
                e = e + 1
                result.append([u, v, w])
                min_cost += w
                self.connect_subtrees(parent, subtree_sizes, x, y)
        return result, min_cost

# TODO: Add pytest and tox for automated tests


def solve():
    edges = [[0, 1, 4],
             [0, 3, 3],
             [0, 4, 5],
             [1, 2, 2],
             [2, 3, 1]]

    g = Graph(vertices=5, edges=edges)
    r, m = g.kruskals_mst()

    print("=== Kruskal's MST ===")
    res = Graph(vertices=5, edges=r)
    res.print()
    print("min cost: {}".format(m))


solve()
