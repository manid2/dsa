GIT_ROOT:=$(shell git rev-parse --show-toplevel)

include $(GIT_ROOT)/mk/common.mk

VENV_DIR:=$(GIT_ROOT)/.venv
VENV_BIN_DIR:=$(VENV_DIR)/bin
VENV_ACTIVATE:=. $(VENV_BIN_DIR)/activate;
VENV_DONE:=$(VENV_DIR)/done
