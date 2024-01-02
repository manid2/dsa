===================
Bactrack algorithms
===================

Backtracking algorithm is used when there are multiple solutions to a problem
and all solutions are desired. It uses brute force approach to recursively
find all possible solutions to the problem and pick the ones matching a
predefined set of conditions. 

Solutions are found by constructing a tree structure called State Space Tree
(SST) traversing Depth-First (DFS).

Abstract backtrack algorithm class
==================================

.. literalinclude:: ../../backtrack/backtrack.py

Arrange seats for 2 Boys and 1 Girl
===================================

.. autoclass:: backtrack.ArrangeSeats
   :members:
   :show-inheritance:

.. literalinclude:: ../../backtrack/arrange_seats.py

Place N Queens in (N x N) chess board
=====================================

.. autoclass:: backtrack.NQueens
   :members:
   :show-inheritance:

.. literalinclude:: ../../backtrack/n_queens.py
