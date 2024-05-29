all: tests check docs

DSAVENV_ACTIVATE_FILE:=.dsavenv/bin/activate
DSAVENV_ACTIVATE_CMD:=. $(DSAVENV_ACTIVATE_FILE);
DSA_PYTHON_MODULES:=$(sort $(dir $(shell git ls-files -- '*/__init__.py')))
CPP_SRC_FILES:=$(shell git ls-files -- '**/*.cpp' '**/*.c')

PYLINT_CMD:=pylint --rcfile=.pylintrc.toml

.PHONY: .dsavenv tests check clean lint format tags docs clean-docs

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

cpp-format:
	clang-format -i $(CPP_SRC_FILES)

py-format: .dsavenv
	$(DSAVENV_ACTIVATE_CMD) autopep8 -iar $(DSA_PYTHON_MODULES)

format: cpp-format py-format

tags:
	./mktags

docs:
	make -C docs

clean-docs:
	make -C docs clean
