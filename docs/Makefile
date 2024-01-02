SPHINXBUILD   = sphinx-build
SPHINXOPTS    =
SOURCEDIR     = .
BUILDDIR      = output

html:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

# TODO Output in html, pdf, man and python help docs

all: html

clean:
	rm -rf "$(BUILDDIR)"

.PHONY: html clean
