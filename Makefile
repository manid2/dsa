# ============================================================================
# Default targets
# ============================================================================
all: tests check

# ============================================================================
# Targets for sub directories
# ============================================================================
SUB_DIRS:=c cpp python3 docs

TESTS_SUB_DIRS:=$(foreach subdir,$(SUB_DIRS),tests-$(subdir))
CHECK_SUB_DIRS:=$(foreach subdir,$(SUB_DIRS),check-$(subdir))
CLEAN_SUB_DIRS:=$(foreach subdir,$(SUB_DIRS),clean-$(subdir))

FORMAT_SUB_DIRS:=$(foreach subdir,$(SUB_DIRS),format-$(subdir))
LINT_SUB_DIRS:=$(foreach subdir,$(SUB_DIRS),lint-$(subdir))

$(SUB_DIRS): venv
	make -C $@

$(TESTS_SUB_DIRS): venv
	make -C $(@:tests-%=%) tests

$(CHECK_SUB_DIRS): $(TESTS_SUB_DIRS)
	make -C $(@:check-%=%) check

$(CLEAN_SUB_DIRS):
	make -C $(@:clean-%=%) clean

$(FORMAT_SUB_DIRS):
	make -C $(@:format-%=%) format

$(LINT_SUB_DIRS):
	make -C $(@:lint-%=%) lint

# ============================================================================
# Setup venv for python and docs
# ============================================================================
include mk/venv.mk

venv: $(VENV_DONE)

$(VENV_DONE): requirements.txt
	test -d $(VENV_DIR) || python3 -m venv $(VENV_DIR)
	$(VENV_ACTIVATE) pip install -Ur requirements.txt
	touch $(VENV_DONE)

# ============================================================================
# Targets for C++ binaries
# ============================================================================
CPP_SRCS:=$(shell $(GIT_LS) -- 'cpp/**/*.cpp')
CPP_BINS:=$(CPP_SRCS:.cpp=)

CPP_BINS_CHECK:=$(addsuffix -check,$(CPP_BINS))
CPP_BINS_CLEAN:=$(addsuffix -clean,$(CPP_BINS))
CPP_SRCS_FORMAT:=$(addsuffix -format,$(CPP_BINS))
CPP_SRCS_LINT:=$(addsuffix -lint,$(CPP_BINS))

CPP_ALL:=$(CPP_BINS) $(CPP_BINS_CLEAN) $(CPP_SRCS_FORMAT) $(CPP_SRCS_LINT)

$(CPP_BINS_CHECK):
	@make --no-print-directory -C cpp $(@:cpp/%=%)

$(CPP_ALL):
	make -C cpp $(@:cpp/%=%)

# ============================================================================
# Top level targets
# ============================================================================
tests: $(TESTS_SUB_DIRS)

check: $(CHECK_SUB_DIRS)

clean: $(CLEAN_SUB_DIRS)
	rm -rf $(VENV_DIR)

format: $(FORMAT_SUB_DIRS)

lint: $(LINT_SUB_DIRS)

tags:
	./mktags

.PHONY: venv tests check clean format lint tags $(SUB_DIRS) $(CLEAN_SUB_DIRS)\
	$(TESTS_SUB_DIRS) $(FORMAT_SUB_DIRS) $(LINT_SUB_DIRS) $(CPP_ALL) \
	$(CPP_BINS_CHECK)
