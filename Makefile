INCLUDE_DIR := include
SRC_DIR     := src
OBJ_DIR     := obj
BIN_DIR     := bin

CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)

TARGET := $(BIN_DIR)/main

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all:
	$(MAKE) -j$(shell nproc) build

build: directories $(TARGET)

directories:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

rebuild: clean all

.PHONY: all build clean rebuild run directories