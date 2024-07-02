from graphs import MAX_WEIGHT


def prims_mst(graph):
    """
    Prim's algorithm to find the Minimum Spanning Tree (MST)

    Refer:

    * `Prim's algorithm | favtutor <fv1>`_

    .. _fv1: https://favtutor.com/blogs/prims-algorithm-python
    """

    # Keep a list of selected nodes to ensure they are not picked twice
    selected_nodes = [False for node in range(graph.vertices)]

    # Result MST edges and min cost
    result = graph.get_init_edges()
    min_cost = 0

    while False in selected_nodes:

        # Use infinite weight to select the initial minimum weight
        min_weight = MAX_WEIGHT
        a = b = 0

        for i in range(graph.vertices):
            if not selected_nodes[i]:
                continue

            # If a node (i) is selected then check if it has a minimum
            # cost path to another unselected node (j)
            for j in range(graph.vertices):
                if selected_nodes[j]:
                    continue

                if not graph.edges[i][j]:
                    continue

                if graph.edges[i][j] < min_weight:
                    min_weight = graph.edges[i][j]
                    a, b = i, j

        if min_weight == MAX_WEIGHT:
            min_weight = 0

        selected_nodes[b] = True
        result[a][b] = result[b][a] = min_weight
        min_cost += min_weight

    return result, min_cost
