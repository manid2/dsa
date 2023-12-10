from .graph import Graph


class MatrixGraph(Graph):
    """This graph is represented using adjacency matrix"""

    def get_init_edges(self):
        return [[self.init for col in range(self.vertices)]
                for row in range(self.vertices)]

    def is_valid_edges(self, edges):
        return (self.vertices == len(edges) and
                self.vertices == len(edges[0]))

    def print(self):
        for i in range(self.vertices):
            for j in range(0 + i, self.vertices):
                if self.edges[i][j]:
                    print(f"{i}-{j}: {self.edges[i][j]}")


class DirectedMatrixGraph(MatrixGraph):
    def no_edge(self, a, b):
        return self.edges[a][b] == self.init

    def add_valid_edge(self, a, b, weight):
        self.edges[a][b] = weight


class UndirectedMatrixGraph(MatrixGraph):
    def no_edge(self, a, b):
        return self.edges[a][b] == self.init and self.edges[a][b] == self.init

    def add_valid_edge(self, a, b, weight):
        self.edges[a][b] = self.edges[b][a] = weight
