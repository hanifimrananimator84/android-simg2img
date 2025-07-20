# =============================================
# android-simg2img Makefile v4.1 (2021 Redesign)
# =============================================

# Project configuration
PROJECT      := android-simg2img
VERSION      := 4.1.0
BUILD_DIR    := build
BIN_DIR      := $(BUILD_DIR)/bin
LIB_DIR      := $(BUILD_DIR)/lib
SRC_DIR      := src
INCLUDE_DIR  := include
THIRD_PARTY  := third_party

# Toolchain configuration
CXX         ?= g++
CC          ?= gcc
AR          ?= ar
RANLIB      ?= ranlib
STRIP       ?= strip
PKG_CONFIG  ?= pkg-config

# Modern build flags (2021 standards)
BASE_FLAGS   := -std=c++17 -I$(INCLUDE_DIR) -I$(THIRD_PARTY)
WARNING_FLAGS := -Wall -Wextra -Wpedantic \
                -Wconversion -Wsign-conversion \
                -Wnull-dereference -Wduplicated-cond

# Feature flags
FEATURES     := -DSPARSEUTILS_HAS_IMG_DISPLAY=1 \
                -DSPARSEUTILS_HAS_BATCH_MODE=1

# Platform detection
ifeq ($(OS),Windows_NT)
    PLATFORM      := windows
    EXE_EXT       := .exe
    LDFLAGS       += -static -lshlwapi -lssp
    CXXFLAGS      += -D_WIN32_WINNT=0x0A00
else
    PLATFORM      := unix
    EXE_EXT       := 
    LDFLAGS       += -rdynamic
endif

# Dependency libraries
LDLIBS       := -lz $(shell $(PKG_CONFIG) --libs ncurses)

# File collections
LIB_SOURCES  := $(wildcard $(SRC_DIR)/lib/*.cpp)
LIB_OBJECTS  := $(patsubst $(SRC_DIR)/lib/%.cpp,$(BUILD_DIR)/lib/%.o,$(LIB_SOURCES))

TOOLS        := simg2img img2simg imgdisplay simg_analyzer
TOOL_SOURCES := $(addprefix $(SRC_DIR)/tools/,$(addsuffix .cpp,$(TOOLS)))
TOOL_OBJECTS := $(patsubst $(SRC_DIR)/tools/%.cpp,$(BUILD_DIR)/tools/%.o,$(TOOL_SOURCES))

# Build rules
.PHONY: all lib tools install clean

all: lib tools

lib: $(LIB_DIR)/libsparse.a

tools: $(addprefix $(BIN_DIR)/,$(addsuffix $(EXE_EXT),$(TOOLS)))

$(LIB_DIR)/libsparse.a: $(LIB_OBJECTS)
	@printf "\033[36m[AR]\033[0m  Creating $@\n"
	@mkdir -p $(@D)
	@$(AR) rcs $@ $^
	@$(RANLIB) $@
	@printf "\033[32m[✓]\033[0m  Library built\n"

define BUILD_TOOL
$(BIN_DIR)/$(1)$(EXE_EXT): $(BUILD_DIR)/tools/$(1).o $(LIB_DIR)/libsparse.a
	@printf "\033[36m[LD]\033[0m  Linking $$@\n"
	@mkdir -p $$(@D)
	@$(CXX) $$(CXXFLAGS) -o $$@ $$^ $$(LDFLAGS) $$(LDLIBS)
	@printf "\033[32m[✓]\033[0m  Tool built: $$(notdir $$@)\n"
endef

$(foreach tool,$(TOOLS),$(eval $(call BUILD_TOOL,$(tool))))

# Pattern rules
$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/lib/%.cpp
	@printf "\033[36m[CXX]\033[0m $<\n"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(BASE_FLAGS) $(WARNING_FLAGS) $(FEATURES) -c $< -o $@

$(BUILD_DIR)/tools/%.o: $(SRC_DIR)/tools/%.cpp
	@printf "\033[36m[CXX]\033[0m $<\n"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(BASE_FLAGS) $(WARNING_FLAGS) $(FEATURES) -c $< -o $@

# Installation
install: all
	@echo "[INSTALL] Installing to /usr/local"
	@install -d /usr/local/{bin,lib,include/sparse}
	@install -m 0755 $(BIN_DIR)/* /usr/local/bin
	@install -m 0644 $(LIB_DIR)/libsparse.a /usr/local/lib
	@cp -r $(INCLUDE_DIR)/sparse/* /usr/local/include/sparse
	@echo "[✓]  Installation complete"

# Clean
clean:
	@echo "[CLEAN] Removing build artifacts"
	@rm -rf $(BUILD_DIR)
	@echo "[✓]  Clean complete"

# Test
test: lib
	@echo "[TEST] Building test suite"
	@mkdir -p $(BUILD_DIR)/tests
	@$(CXX) $(CXXFLAGS) tests/*.cpp $(LIB_DIR)/libsparse.a -lgtest -lgtest_main -o $(BUILD_DIR)/tests/run_tests
	@echo "[✓]  Test executable built: build/tests/run_tests"

# Help
help:
	@echo "Android sparse image tools v$(VERSION)"
	@echo "Targets:"
	@echo "  all       - Build everything (default)"
	@echo "  lib       - Build only the library"
	@echo "  tools     - Build only the tools"
	@echo "  install   - Install system-wide"
	@echo "  test      - Build and run tests"
	@echo "  clean     - Remove build artifacts"
	@echo "  help      - Show this message"
