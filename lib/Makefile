CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lpcap

# Get all .c and .cpp files in the current directory
C_FILES := $(wildcard *.c)
CPP_FILES := $(wildcard *.cpp)

# Generate object file names for each source file
OBJ_FILES := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)

# Main target
all: program

# Rule to compile C files
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C++ files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create executable
program: $(OBJ_FILES)
    $(CXX) $^ -o $@ $(LDFLAGS)

# Clean up
clean:
    rm -f program $(OBJ_FILES)
