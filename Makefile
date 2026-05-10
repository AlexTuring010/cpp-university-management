CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
BUILD_DIR = build
OBJ_DIR = obj
INCLUDE_DIR = includes
SRCS = $(wildcard src/*.cpp) main.cpp
OBJS = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/my_program
INCFLAGS = -I ./$(INCLUDE_DIR)

all: $(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

$(OBJS): | $(OBJ_DIR)
$(TARGET): | $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
