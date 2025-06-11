# Compiler and flags
CXX := clang++
CXXFLAGS := -g -O3 -std=c++17

LLVM_CXXFLAGS := $(shell llvm-config --cxxflags)
LLVM_LDFLAGS := $(shell llvm-config --ldflags --system-libs --libs core)

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN := a.out

# Collect all .cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Link object files into binary
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LLVM_LDFLAGS)

# Compile .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) -c $< -o $@

# tests
test:
	./a.out tests/test_1.cpp

# Clean build
clean:
	rm -rf $(BUILD_DIR) $(BIN)
