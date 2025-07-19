CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

# Build directory
BUILD_DIR = ${output_dir}
BUILD_DIR_ABS = $(abspath $(BUILD_DIR))

MiniMPL_INCLUDE = ../../MiniMPL/include
MiniMPL_INCLUDE_ABS = $(abspath $(MiniMPL_INCLUDE))

SRC_DIR=../
SRC_DIR_ABS = $(abspath $(SRC_DIR))

CXXFLAGS += -I${SRC_DIR_ABS} -I${MiniMPL_INCLUDE_ABS}

# Source files (absolute paths)
HEADERS_ABS = ${SRC_DIR_ABS}/3_symbol_bloat_optimize.hpp
DEMO_SRC_ABS = $(abspath ./3_symbol_bloat_optimize_demo.cpp)
# SIMPLE_SRC_ABS = $(abspath ./simple_demo.cpp)
BASE_CRTP_SRC_ABS = ./1_base_crtp_demo.cpp
ENHANCED_SRC_ABS = ./2_enhanced_crtp_trait_bind_demo.cpp

# Target executables (absolute paths)
DEMO_TARGET_ABS = $(BUILD_DIR_ABS)/3_symbol_bloat_optimize_demo
# SIMPLE_TARGET_ABS = $(BUILD_DIR_ABS)/simple_demo
BASE_TARGET_ABS = $(BUILD_DIR_ABS)/1_base_demo
ENHANCED_TARGET_ABS = $(BUILD_DIR_ABS)/2_enhanced_demo

# Compatibility with relative paths
HEADERS = ${SRC_DIR_ABS}/3_symbol_bloat_optimize.hpp
SYMBOL_BLOAT_OPTIMIZE_SRC = ./3_symbol_bloat_optimize_demo.cpp
BASIC_SRC = ./1_base_crtp_demo.cpp ./2_enhanced_crtp_trait_bind_demo.cpp
SYMBOL_BLOAT_OPTIMIZE_TARGET = $(BUILD_DIR)/3_symbol_bloat_optimize_demo
BASIC_TARGETS = $(BUILD_DIR)/1_base_demo $(BUILD_DIR)/2_enhanced_demo

# Default target
.PHONY: all clean symOptimize basic help clean-build

all: symOptimize basic

# Ensure clean build directory
clean-build:
	@echo "Setting up clean build environment..."
	@if [ -d "$(BUILD_DIR_ABS)" ]; then \
		echo "Removing existing build directory: $(BUILD_DIR_ABS)"; \
		rm -rf $(BUILD_DIR_ABS); \
	fi
	@echo "Creating fresh build directory: $(BUILD_DIR_ABS)"
	@mkdir -p $(BUILD_DIR_ABS)

# Advanced demo
symOptimize: clean-build $(SYMBOL_BLOAT_OPTIMIZE_TARGET)

$(SYMBOL_BLOAT_OPTIMIZE_TARGET): $(SYMBOL_BLOAT_OPTIMIZE_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET_ABS) $(DEMO_SRC_ABS)
	echo === symbol optimize Demo ===
	nm -s $(DEMO_TARGET_ABS) | grep "dump_type_info_" | sort -t'_' -k3
	echo "" 

# Basic demos
basic: clean-build $(BASIC_TARGETS)

$(BUILD_DIR)/1_base_demo: ./1_base_crtp_demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(BASE_TARGET_ABS) $(BASE_CRTP_SRC_ABS)

$(BUILD_DIR)/2_enhanced_demo: ./2_enhanced_crtp_trait_bind_demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(ENHANCED_TARGET_ABS) $(ENHANCED_SRC_ABS)

# Test targets
test-advanced: symOptimize
	@echo "=== Running Advanced Value-to-Type Binding Demo ==="
	@./$(SYMBOL_BLOAT_OPTIMIZE_TARGET)
	@echo ""
	@echo "=== Advanced symOptimize completed successfully! ==="

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts from: $(BUILD_DIR_ABS)"
	@rm -rf $(BUILD_DIR_ABS)
	@rm -f $(abspath *.o)
	@echo "Clean completed."

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build all demos in clean build directory"
	@echo "  symOptimize  - Build advanced value-binding demo"
	@echo "  basic        - Build basic CRTP demos"
	@echo "  test-advanced- Run the advanced demo"
	@echo "  clean        - Remove build directory and artifacts"
	@echo "  clean-build  - Set up clean build environment"
	@echo "  help         - Show this help message"
	@echo ""
	@echo ""
	@echo "Absolute Project Paths:"
	@echo "  Current Dir: $(abspath .)"
	@echo "  Build Dir:   $(BUILD_DIR_ABS)"
	@echo "  Header:      $(HEADERS_ABS)"
	@echo "  Demo Src:    $(DEMO_SRC_ABS)"
	@echo "  Base Src:    $(BASE_CRTP_SRC_ABS)"
	@echo "  Enhanced:    $(ENHANCED_SRC_ABS)"
	@echo ""
	@echo "Advanced Value-to-Type Binding System"
	@echo "Author: Shen Xiaolong (申晓龙)"
	@echo "Repository: https://github.com/shenxiaolong-code/mlir-crtp-proposal"