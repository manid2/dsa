# Configuration file for the Sphinx documentation builder.

# -- Modules path
import os
import sys
sys.path.insert(0, os.path.abspath('..'))

# -- Project information
project = 'Data structures and algorithms'
copyright = 'Mani Kumar'
author = 'Mani Kumar'
version = '1.0.0'

# -- General configuration
extensions = [
    'sphinx.ext.duration',
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.intersphinx',
]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

# -- Options for HTML output
html_theme = 'sphinx_rtd_theme'