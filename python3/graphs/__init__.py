# flake8: noqa: F401

import math

from .matrix_graph import MatrixGraph, DirectedMatrixGraph, UndirectedMatrixGraph
from .list_graph import ListGraph, DirectedListGraph, UndirectedListGraph
from .graph import Graph

MAX_WEIGHT = math.inf


class NegativeCycleError(Exception):
    def __init__(self, message="Negative cycle found"):
        self.message = message

    def __str__(self):
        return self.message
