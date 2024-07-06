# ============================================================================
# Default targets
# ============================================================================
all: tests check

# ============================================================================
# Variables & source file targets
# ============================================================================
include ../mk/common.mk

CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

BUILD_DIR:=build

SRCS:=$(shell $(GIT_LS) -- '**/*.cpp')
BINS:=$(patsubst %.cpp,$(BUILD_DIR)/%,$(SRCS:.cpp=))

$(BINS): %: $(BUILD_DIR)/%.o
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/$*.o

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

BINS_CHECK:=$(addsuffix -check,$(BINS))
BINS_CLEAN:=$(addsuffix -clean,$(BINS))
SRCS_FORMAT:=$(addsuffix -format,$(BINS))
SRCS_LINT:=$(addsuffix -lint,$(BINS))

$(BINS_CHECK):
	@make -s $(@:-check=)
	@./$(BUILD_DIR)/$(@:-check=)

$(BINS_CLEAN):
	rm -f $(BUILD_DIR)/$(@:-clean=.o) $(BUILD_DIR)/$(@:-clean=)

$(SRCS_FORMAT):
	clang-format -i $(addsuffix .cpp,$(@:-format=))

$(SRCS_LINT):
	@echo "TODO lint $(addsuffix .cpp,$(@:-lint=))"

# ============================================================================
# Top level targets
# ============================================================================
tests: $(BINS)

check:

clean:
	rm -rf $(BINS)

format:

lint:

.PHONY: tests check clean format lint $(BINS_CHECK) $(BINS_CLEAN) \
	$(SRCS_FORMAT) $(SRCS_LINT)
