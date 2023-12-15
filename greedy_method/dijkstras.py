from queue import PriorityQueue

from graphs import MAX_WEIGHT


def dijkstras_path(start, graph):
    """
    Dijkstra's algorithm to find single source shortest path to all nodes.

    Refer:

    * `Dijkstra's algorithm | stackabuse <sa1>`_

    # noqa: E501
    .. _sa1: https://stackabuse.com/courses/graphs-in-python-theory-and-implementation/lessons/dijkstras-algorithm/
    """

    d = {v: MAX_WEIGHT for v in range(graph.vertices)}
    d[start] = 0

    pq = PriorityQueue()
    pq.put((d[start], start))

    visited = set()

    while not pq.empty():
        du, u = pq.get()
        visited.add(u)

        for v in range(graph.vertices):
            if graph.no_edge(u, v) or v in visited:
                continue

            dist = du + graph.edges[u][v]
            if dist < d[v]:
                pq.put((dist, v))
                d[v] = dist
    return d
