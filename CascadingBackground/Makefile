# C++ compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# External libraries to include
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system

# Build all targets
all: CascadingBackground

CascadingBackground:
	$(CC) $(CFLAGS) ./src/CascadingBackground.cpp -o CascadingBackground $(LIBRARIES)

clean:
	rm CascadingBackground
