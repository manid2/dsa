#!/usr/bin/env python3

from queue import PriorityQueue


# This graph is represented using adjacency matrix
class Graph:
    def __init__(self, num_of_nodes):
        self.vertices = num_of_nodes
        self.edges = [[-1 for i in range(self.vertices)]
                      for j in range(self.vertices)]
        self.visited = []

    def add_edge(self, node1, node2, weight):
        self.edges[node1][node2] = self.edges[node2][node1] = weight

    def dijkstra_path(self, start_vertex):
        D = {v:float('inf') for v in range(self.vertices)}
        D[start_vertex] = 0

        pq = PriorityQueue()
        pq.put((0, start_vertex))

        while not pq.empty():
            (dist, current_vertex) = pq.get()
            self.visited.append(current_vertex)

            for neighbor in range(self.vertices):
                if self.edges[current_vertex][neighbor] != -1:
                    distance = self.edges[current_vertex][neighbor]
                    if neighbor not in self.visited:
                        old_cost = D[neighbor]
                        new_cost = D[current_vertex] + distance
                        if new_cost < old_cost:
                            pq.put((new_cost, neighbor))
                            D[neighbor] = new_cost
        return D

    def print_path(self, D):
        for vertex in range(len(D)):
            print("Distance from vertex 0 to vertex", vertex, "is", D[vertex])

# TODO: Trace code and fix issues
def solve():
    g = Graph(9)
    g.add_edge(0, 1, 4)
    g.add_edge(0, 2, 7)
    g.add_edge(1, 2, 11)
    g.add_edge(1, 3, 9)
    g.add_edge(1, 5, 20)
    g.add_edge(2, 5, 1)
    g.add_edge(3, 6, 6)
    g.add_edge(3, 4, 2)
    g.add_edge(4, 6, 10)
    g.add_edge(4, 8, 15)
    g.add_edge(4, 7, 5)
    g.add_edge(4, 5, 1)
    g.add_edge(5, 7, 3)
    g.add_edge(6, 8, 5)
    g.add_edge(7, 8, 12)
    result = g.dijkstra_path(0)
    g.print_path(result)

solve()
