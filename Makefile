# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wpedantic -g -I src

# Compiler library flags
LDFLAGS = -lSDL2 -lm

# Source directory
SRC_DIR = src

# List of all .c files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# List of all .o files
OBJS = $(SRCS:.c=.o)

# Output executable name
TARGET = objectsRotator

# Default target
default: all

all: $(TARGET)

run: $(TARGET)
	./$<

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .c files to .o files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
