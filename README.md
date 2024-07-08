Data structures and algorithms (DSA)
====================================

The purpose of this repository is to help me prepare for online assessments,
programming competitions and software engineering interviews along with the
benefit of practicing in the programming language I currently (year 2024) work
in i.e. C++.

I had used C and Python 3 for previous practice sessions so that code is
retained but no new code is pushed due to me using C++ full time so I gain
expertise in that.

For these practice programs I have borrowed working code from various online
sources and relevant credits are given in code comments. So I hope anyone who
finds this repository may use it for their own learning of data structures and
algorithms. After learning from working solutions in this repository you may
practice solving problems on coding contest platforms with time limit.

Use the code and documentation in this repository freely and share it with the
others.

Coding guidelines
-----------------

* Focus on C++ code and for online assessments, coding competition especially
  for platforms such as HackerRank, LeetCode.
* Fully working single source files with no external dependencies as required
  for coding competitions.
* Every C++ source file must build & run as a single file target the focus is
  on solving the problem correctly.
* Each C++ compiled binary must output test result as a single line in this
  fomrat `Executed M implementations with N tests.`. This makes it easy to
  get tests summary.
* For debugging each binary must print test name, test case number with input
  and output in this format and only when enabled with environment variable
  `SHOW_TEST_OUTPUT`:

  ```text
  Testing implementation M <Name>
    test-0:  input: <i1 = v1>, <iX = vX>  output: <o = v>
    ...
    test-N:  input: <i1 = v1>, <iX = vX>  output: <o = v>
  Executed M implementations with N tests.
  ```

* Must use latest C++ version (as of now C++20) to be updated with the latest
  additions, improvements to C++ and STL library.

Build & test
------------

This repository uses Gnu Makefile to run build and test tasks along with some
helper tasks such as to run formatter, linter for source code.

### Examples

```bash
make venv # setup python virtual environment
make docs # generate sphinx docs

make cpp/arrays/2sum-01        # build a test binary from .cpp source file
make cpp/arrays/2sum-01-check  # run the test binary
make cpp/arrays/2sum-01-format # format .cpp source file

SHOW_TEST_OUTPUT=1 make cpp/arrays/2sum-01-check # run test with debug output
```
