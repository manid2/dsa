from abc import ABC, abstractmethod


class Graph(ABC):
    """
    This is a generic graph.

    It provides interfaces to implement a graph using adjacency matrix or
    list.
    """

    def __init__(self, vertices=0, edges=None, init=0):
        self.init = init
        self.vertices = vertices

        if edges and self.is_valid_edges(edges):
            self.edges = edges
        else:
            self.edges = self.get_init_edges()

    @abstractmethod
    def get_init_edges(self):
        pass

    @abstractmethod
    def is_valid_edges(self, edges):
        pass

    @abstractmethod
    def add_valid_edge(self, a, b, weight):
        pass

    def add_edges(self, edges):
        """Add all edges as adjacency matrix or list to the graph"""
        if self.is_valid_edges(edges):
            self.edges = edges
        else:
            raise ValueError("Invalid adjacency matrix, " +
                             "a valid matrix must be " +
                             f"{self.vertices} x {self.vertices}")

    @abstractmethod
    def no_edge(self, a, b):
        pass

    @abstractmethod
    def print(self):
        pass

    def add_edge(self, a, b, weight):
        if self.is_valid_node(a) and self.is_valid_node(b):
            self.add_valid_edge(a, b, weight)
        else:
            raise ValueError(f"Invalid nodes {a}, {b}, " +
                             "a valid node is in range " +
                             f"[0, {self.vertices - 1}]")

    def has_edge(self, a, b):
        return not self.no_edge(a, b)

    def is_valid_node(self, a):
        return -1 < a < self.vertices
