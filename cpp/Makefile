# ============================================================================
# Default targets
# ============================================================================
all: tests check

# ============================================================================
# Variables & source file targets
# ============================================================================
include ../mk/common.mk

CXX = /usr/bin/g++

SYS_NAME:=$(shell uname -s)
IS_CYGWIN:=$(findstring CYGWIN, $(SYS_NAME))
IS_MACOS:=$(findstring Darwin, $(SYS_NAME))

ifeq ($(IS_MACOS), Darwin)
  CXX = /usr/local/bin/g++
endif

MIN_GPP_VERSION=13
GPP_VERSION:=$(shell $(CXX) -dumpfullversion | cut -d. -f1)
CHECK_GPP_VERSION:=$(shell expr "$(GPP_VERSION)" ">=" "$(MIN_GPP_VERSION)")

ifneq "$(CHECK_GPP_VERSION)" "1"
  $(error ERROR: $(CXX) version $(GPP_VERSION) is lower than required \
          minimum version $(MIN_GPP_VERSION))
endif

CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -Iincludes

ifeq ($(IS_CYGWIN), CYGWIN)
  CXXFLAGS += -static-libstdc++
endif

BUILD_DIR:=build

HDRS:=$(shell $(GIT_LS) -- 'includes/*.h')
SRCS:=$(shell $(GIT_LS) -- '**/*.cpp')
BINS:=$(patsubst %.cpp,$(BUILD_DIR)/%,$(SRCS:.cpp=))

$(BINS): %: $(BUILD_DIR)/%.o
	$(Q)$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/$*.o

$(BUILD_DIR)/%.o: %.cpp $(HDRS)
	$(Q)mkdir -p $(@D)
	$(Q)$(CXX) $(CXXFLAGS) -c -o $@ $<

BINS_CHECK:=$(addsuffix -check,$(BINS))
BINS_CLEAN:=$(addsuffix -clean,$(BINS))
SRCS_FORMAT:=$(addsuffix -format,$(BINS))
SRCS_LINT:=$(addsuffix -lint,$(BINS))

$(BINS_CHECK):
	$(Q)$(MAKE) $(@:-check=)
	$(Q)./$(BUILD_DIR)/$(@:-check=)

$(BINS_CLEAN):
	rm -f $(BUILD_DIR)/$(@:-clean=.o) $(BUILD_DIR)/$(@:-clean=)

$(SRCS_FORMAT):
	clang-format -i $(addsuffix .cpp,$(@:-format=))

$(SRCS_LINT):
	$(Q)echo "TODO lint $(addsuffix .cpp,$(@:-lint=))"

# ============================================================================
# Top level targets
# ============================================================================
tests: $(BINS)

check:
	$(Q)cd .. && scripts/run_tests.py

clean:
	rm -rf $(BINS)

format: $(SRCS_FORMAT)

lint:

.PHONY: tests check clean format lint $(BINS_CHECK) $(BINS_CLEAN) \
	$(SRCS_FORMAT) $(SRCS_LINT)
