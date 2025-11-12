# Makefile wrapper for CMake build

# Build directories
BUILD_DIR := build
DEBUG_DIR := $(BUILD_DIR)
RELEASE_DIR := $(BUILD_DIR)

# Binary output
BINARY := bin/main

# Default target
.PHONY: all
all: release

# Release build
.PHONY: release
release:
	@echo "Building release..."
	@mkdir -p $(RELEASE_DIR)
	@cd $(RELEASE_DIR) && cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
	@cd $(RELEASE_DIR) && ninja
	@echo "Release build complete: $(RELEASE_DIR)/$(BINARY)"

# Debug build
.PHONY: debug
debug:
	@echo "Building debug..."
	@mkdir -p $(DEBUG_DIR)
	@cd $(DEBUG_DIR) && cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..
	@cd $(DEBUG_DIR) && ninja
	@echo "Debug build complete: $(DEBUG_DIR)/$(BINARY)"

# Run release build
.PHONY: run
run: release
	@echo "Running release build..."
	@$(RELEASE_DIR)/$(BINARY)

# Run debug build
.PHONY: run-debug
run-debug: debug
	@echo "Running debug build..."
	@$(DEBUG_DIR)/$(BINARY)

# Debug with GDB
.PHONY: gdb
gdb: debug
	@echo "Starting GDB..."
	@gdb $(DEBUG_DIR)/$(BINARY)

# Debug with LLDB
.PHONY: lldb
lldb: debug
	@echo "Starting LLDB..."
	@lldb $(DEBUG_DIR)/$(BINARY)

# Test (runs CMake tests if configured)
.PHONY: test
test: release
	@echo "Running tests..."
	@cd $(RELEASE_DIR) && ctest --output-on-failure

# Install
.PHONY: install
install: release
	@echo "Installing..."
	@cd $(RELEASE_DIR) && cmake --install .

# Clean all builds
.PHONY: clean
clean:
	@echo "Cleaning all build directories..."
	@rm -rf $(BUILD_DIR) $(DEBUG_DIR) $(RELEASE_DIR)
	@echo "Clean complete"

# Clean release only
.PHONY: clean-release
clean-release:
	@echo "Cleaning release build..."
	@rm -rf $(RELEASE_DIR)

# Clean debug only
.PHONY: clean-debug
clean-debug:
	@echo "Cleaning debug build..."
	@rm -rf $(DEBUG_DIR)

# Rebuild release
.PHONY: rebuild
rebuild: clean-release release

# Rebuild debug
.PHONY: rebuild-debug
rebuild-debug: clean-debug debug

# Show help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make               - Build release (default)"
	@echo "  make release       - Build release version"
	@echo "  make debug         - Build debug version"
	@echo "  make run           - Build and run release"
	@echo "  make run-debug     - Build and run debug"
	@echo "  make gdb           - Build debug and start GDB"
	@echo "  make lldb          - Build debug and start LLDB"
	@echo "  make test          - Run tests"
	@echo "  make install       - Install the binary"
	@echo "  make clean         - Remove all build directories"
	@echo "  make clean-release - Remove release build only"
	@echo "  make clean-debug   - Remove debug build only"
	@echo "  make rebuild       - Clean and rebuild release"
	@echo "  make rebuild-debug - Clean and rebuild debug"
	@echo "  make help          - Show this help message"
