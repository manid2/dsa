def floyd_warshall(graph):
    """
    Floyd-Warshall algorithm to find all pairs shortest path

    Refer:

    * `Floyd-Warshall algorithm | pythonalgos <pa1>`_

    .. _pa1: https://pythonalgos.com/2022/02/17/graph-algorithms-floyd-warshall-in-python/ # noqa: E501
    """

    v = range(graph.vertices)
    e = graph.edges

    for k in v:
        for i in v:
            for j in v:
                e[i][j] = min(e[i][j], e[i][k] + e[k][j])
    return e
