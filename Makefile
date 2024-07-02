all: tests check docs

DSAVENV_ACTIVATE_FILE:=.venv/bin/activate
DSAVENV_ACTIVATE_CMD:=. $(DSAVENV_ACTIVATE_FILE);
DSA_PYTHON_MODULES:=$(sort $(dir $(shell git ls-files -- '*/__init__.py')))
CPP_SRC_FILES:=$(shell git ls-files -- '**/*.cpp' '**/*.c')

PYLINT_CMD:=pylint --rcfile=.pylintrc.toml

.PHONY: .venv tests check clean lint format tags docs clean-docs

.venv: .venv/done

.venv/done: requirements.txt
	test -d .venv || python3 -m venv .venv
	$(DSAVENV_ACTIVATE_CMD) pip install -Ur requirements.txt
	touch .venv/done

tests: lint
	touch .venv/testsdone

check: .venv/testsdone
	$(DSAVENV_ACTIVATE_CMD) pytest

clean:
	rm -rf .venv

flake8: .venv
	$(DSAVENV_ACTIVATE_CMD) flake8 $(DSA_PYTHON_MODULES)

pylint: .venv
	$(DSAVENV_ACTIVATE_CMD) $(PYLINT_CMD) $(DSA_PYTHON_MODULES)

lint: flake8 pylint
	$(info Linting OK.)

cpp-format:
	@echo "Formatting cpp source files..."
	@clang-format -i $(CPP_SRC_FILES)

py-format: .venv
	@echo "Formatting python source files..."
	@$(DSAVENV_ACTIVATE_CMD) autopep8 -iar $(DSA_PYTHON_MODULES)

format: cpp-format py-format

tags:
	./mktags

docs:
	make -C docs

clean-docs:
	make -C docs clean
