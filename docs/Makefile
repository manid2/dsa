# ============================================================================
# Default targets
# ============================================================================
all: tests check

all: html

# ============================================================================
# Variables & source file targets
# ============================================================================
include ../mk/venv.mk

SPHINXBUILD   = sphinx-build
SPHINXOPTS    =
SOURCEDIR     = .
BUILDDIR      = output

html: venv
	$(Q)$(VENV_ACTIVATE) $(SPHINXBUILD) -M $@ \
		"$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

venv: $(VENV_DONE)

$(VENV_DONE):
	make -C ../ venv

# ============================================================================
# Top level targets
# ============================================================================
tests: html

check:

clean:
	rm -rf "$(BUILDDIR)"

format:

lint:

.PHONY: tests check clean format lint
