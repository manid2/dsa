from .graph import Graph


class ListGraph(Graph):
    """This graph is represented using adjacency list"""

    def get_init_edges(self):
        return []

    def is_valid_edges(self, edges):
        return True

    def no_edge(self, a, b):
        return True

    def print(self):
        for a, b, weight in self.edges:
            print(f"{a}-{b}: {weight}")


class DirectedListGraph(ListGraph):
    def add_valid_edge(self, a, b, weight):
        self.edges.append([a, b, weight])


class UndirectedListGraph(ListGraph):
    def add_valid_edge(self, a, b, weight):
        self.edges.append([a, b, weight])
        self.edges.append([b, a, weight])
