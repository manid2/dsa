# ============================================================================
# Default targets
# ============================================================================
all: tests check

# ============================================================================
# Variables & source file targets
# ============================================================================
include ../mk/venv.mk

PYLINT:=pylint --rcfile=../.pylintrc.toml

MODULES:=$(sort $(dir $(shell $(GIT_LS) -- '*/__init__.py')))

venv: $(VENV_DONE)

$(VENV_DONE):
	make -C ../ venv

flake8: venv
	$(VENV_ACTIVATE) flake8 $(MODULES)

pylint: venv
	$(VENV_ACTIVATE) $(PYLINT) $(MODULES)

# ============================================================================
# Top level targets
# ============================================================================
tests: lint
	touch $(VENV_DIR)/testsdone

check: $(VENV_DIR)/testsdone
	$(VENV_ACTIVATE) pytest

clean:

format: venv
	$(Q)echo "Formatting python source files..."
	$(Q)$(VENV_ACTIVATE) autopep8 -iar $(MODULES)

lint: flake8 pylint
	$(info Linting OK.)

.PHONY: tests check clean format lint
