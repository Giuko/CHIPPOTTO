CC     = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
TARGET = chippotto

SRC_DIR = src
INC_DIR = src 
BLD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(SRCS))

.PHONY: all run clean

all: $(BLD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile source files directly into build/
$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

# Clean build artifacts and binary
clean:
	rm -rf $(BLD_DIR) $(TARGET)
