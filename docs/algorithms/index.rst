==========
Algorithms
==========

Understand and analyse algorithms with time and space complexities.

What is an algorithm?
=====================

An Algorithm is a step by step procedure to solve a computational problem. It
is different from a computer program which is a set of instructions to be
given to a machine, an algorithm is written in simple English like statements
for human understanding.

Time complexities of loops
==========================

The degree of polynomial is used to write the time and space complexities in
big O notation.

======================  ==================
  Loop                    Time complexity
======================  ==================
for (i=0; i<n; i++)     :math:`O(n)`
for (i=1; i<n; i*=2)    :math:`O(\log_2 n)`
for (i=1; i<n; i*=3)    :math:`O(\log_3 n)`
======================  ==================

Classes of functions
====================

===============================  =============
  Big O                            Time
===============================  =============
:math:`O(1)`                     Constant
:math:`O(\log n), O(n \log n)`   Logarithmic
:math:`O(n)`                     Linear
:math:`O(n^2)`                   Quadratic
:math:`O(n^3)`                   Cubic
:math:`O(2^n), O(3^n), O(n^n)`   Exponential
===============================  =============

Compare classes of functions
============================

.. math::
   :label: algorithm classes comparision

   1 < \log n < \sqrt n < n < n \log n < n^2 < n^3 < ...
   < 2^n < 3^n < ... < n^n

Asymptotic notations
====================

1. Big O - upper bound (also used when theta Θ could not be used)
2. Omega (Ω) - lower bound
3. Theta (Θ) - average bound (useful)
