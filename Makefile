all: tests check

DSAVENV_ACTIVATE_FILE:=.dsavenv/bin/activate
DSAVENV_ACTIVATE_CMD:=. $(DSAVENV_ACTIVATE_FILE);
DSA_PYTHON_MODULES:=$(sort $(dir $(shell git ls-files -- '*/__init__.py')))

PYLINT_CMD:=pylint --rcfile=.pylintrc.toml

.PHONY: .dsavenv tests check clean lint format tags

.dsavenv: .dsavenv/done

.dsavenv/done: requirements.txt
	test -d .dsavenv || python3 -m venv .dsavenv
	$(DSAVENV_ACTIVATE_CMD) pip install -Ur requirements.txt
	touch .dsavenv/done

tests: lint
	touch .dsavenv/testsdone

check: .dsavenv/testsdone
	$(DSAVENV_ACTIVATE_CMD) pytest

clean:
	rm -rf .dsavenv

flake8: .dsavenv
	$(DSAVENV_ACTIVATE_CMD) flake8 $(DSA_PYTHON_MODULES)

pylint: .dsavenv
	$(DSAVENV_ACTIVATE_CMD) $(PYLINT_CMD) $(DSA_PYTHON_MODULES)

lint: flake8 pylint
	$(info Linting OK.)

format: .dsavenv
	$(DSAVENV_ACTIVATE_CMD) autopep8 -iar $(DSA_PYTHON_MODULES)

tags:
	./mktags
