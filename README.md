Data structures and algorithms (DSA)
====================================

Implementation and documentation of data structures and algorithms with tested
code.

Tests
-----

```bash
# create virtual environment
python3 -m venv .dsavenv
source .dsavenv/bin/activate

# install dependencies
(.dsavenv) pip install -Ur requirements.txt

# run pytests
(.dsavenv) pytest

# run pylint
(.dsavenv) pylint ${modules} ${tests}

# run flake8
(.dsavenv) flake8 ${modules} ${tests}

# run autopep8
(.dsavenv) autopep8 -i -a ${modules} ${tests}

# update requirements.txt
(.dsavenv) pip freeze > requirements.txt
```
