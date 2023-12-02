#!/usr/bin/env python3

from queue import PriorityQueue


MAX_WEIGHT = float('inf')


class Graph:
    """This graph is represented using adjacency matrix"""

    def __init__(self, vertices=0, edges=[]):
        self.vertices = vertices if vertices else len(edges)

        if self.is_valid_edges(edges):
            self.edges = edges
        else:
            self.edges = self.get_init_edges()

    def get_init_edges(self):
        return [[-1 for column in range(self.vertices)]
                 for row in range(self.vertices)]

    def is_valid_node(self, a):
        return (a > -1 and a < self.vertices)

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
                              "[0, {}]".format(self.vertices - 1))

    def add_edges(self, edges):
        """Add all edges in the form of adjacency matrix to the graph"""

        if self.is_valid_edges(edges):
            self.edges = edges
        else:
            raise ValueError("Invalid adjacency matrix, " +
                             "a valid matrix must be {} x {}"
                             .format(self.vertices))

    def print(self, start, d):
        for v in range(len(d)):
            print("{0}-{1}: {2}".format(start, v, d[v]))

    def no_edge(self, u, v):
        return self.edges[u][v] == -1

    def dijkstras_path(self, start):
        """
        Dijkstra's algorithm to find single source shortest path to all nodes.

        Refer:

        * https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/dijkstras-algorithm/
        """

        d = {v: MAX_WEIGHT for v in range(self.vertices)}
        d[start] = 0

        pq = PriorityQueue()
        pq.put((d[start], start))

        visited = set()

        while not pq.empty():
            du, u = pq.get()
            visited.add(u)

            for v in range(self.vertices):
                if self.no_edge(u, v) or v in visited:
                    continue

                dist = du + self.edges[u][v]
                if dist < d[v]:
                    pq.put((dist, v))
                    d[v] = dist
        return d

# TODO: Add pytest and tox for automated tests
def solve():
    g = Graph(5)
    g.add_edge(0, 1, 4)
    g.add_edge(0, 3, 3)
    g.add_edge(0, 4, 5)
    g.add_edge(1, 2, 2)
    g.add_edge(2, 3, 1)
    start = 0
    res = g.dijkstras_path(start)

    print("=== Dijkstra's SSSP ===")
    g.print(start, res)

solve()
