# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =
SRC_DIR = src
OBJ_DIR = dist
TARGET = $(OBJ_DIR)/chesso.exe

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Create dist directory if it doesn't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Clean
clean:
	del /q $(subst /,\,$(OBJ_DIR))\*.o
	del /q $(subst /,\,$(TARGET))

# Run
run: $(TARGET)
	$(TARGET)

# Phony targets
.PHONY: all clean run
