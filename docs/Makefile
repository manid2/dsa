DSAVENV_ACTIVATE_FILE:=../.dsavenv/bin/activate
DSAVENV_ACTIVATE_CMD:=. $(DSAVENV_ACTIVATE_FILE);

SPHINXBUILD   = sphinx-build
SPHINXOPTS    =
SOURCEDIR     = .
BUILDDIR      = output

html:
	@$(DSAVENV_ACTIVATE_CMD) $(SPHINXBUILD) -M $@ \
		"$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

# TODO Output in html, pdf, man and python help docs

all: html

clean:
	rm -rf "$(BUILDDIR)"

.PHONY: html clean
