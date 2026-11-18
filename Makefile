# Libraries
LDLIBS = -lm

CC     = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
TARGET = chippotto

SRC_DIR = src
INC_DIR = src
BLD_DIR = build

# Enable Raylib with: make USE_RAYLIB=1
USE_RAYLIB ?= 0

ifeq ($(USE_RAYLIB),1)
    CFLAGS += -D__RAYLIB
    LDLIBS += -lraylib -lGL -lpthread -ldl -lrt -lX11
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(SRCS))

.PHONY: all run clean

all: $(BLD_DIR) $(TARGET)

# Create build directory if it doesn't exist
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $@

# Compile source files directly into build/
$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

clean:
	rm -rf $(BLD_DIR) $(TARGET)
