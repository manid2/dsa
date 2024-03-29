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
templates_path = ['_templates']

# -- Options for HTML output
html_title = 'manid2'
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_favicon = html_static_path[0] + '/awesome_author.svg'
