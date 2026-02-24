# Simple Makefile for PushBox game


SRC_DIR := src
OBJ_DIR := build

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -I$(SRC_DIR)

CHARA_SRCS := $(wildcard $(SRC_DIR)/character/*.cc)
CHARA_OBJS := $(patsubst $(SRC_DIR)/character/%.cc,$(OBJ_DIR)/character/%.o,$(CHARA_SRCS))

STAGE_SRCS := $(wildcard $(SRC_DIR)/stage/*.cc)
STAGE_OBJS := $(patsubst $(SRC_DIR)/stage/%.cc,$(OBJ_DIR)/stage/%.o,$(STAGE_SRCS))

SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRCS))

TARGET := push_box

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# rule for character subdirectory objects
$(OBJ_DIR)/character/%.o: $(SRC_DIR)/character/%.cc
	@mkdir -p $(OBJ_DIR)/character
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@
$(OBJ_DIR)/stage/%.o: $(SRC_DIR)/stage/%.cc
	@mkdir -p $(OBJ_DIR)/stage
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@
$(TARGET): $(CHARA_OBJS) $(STAGE_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
.PHONY: all clean