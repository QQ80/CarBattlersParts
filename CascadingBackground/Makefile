# C++ compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# External libraries to include
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system
LIBDIR = ./ext
SFMLVER = 2.3.2
SEARCHDIR = -L../ext/SFML-$(SFMLVER)/lib/ -I../ext/SFML-$(SFMLVER)/include

# Build all targets
all: CascadingBackground

CascadingBackground:
	if [ ! -d "../ext" ]; then $(CC) $(CFLAGS) ./src/CascadingBackground.cpp -o CascadingBackground $(LIBRARIES); else $(CC) $(CFLAGS) ./src/CascadingBackground.cpp -o CascadingBackground $(SEARCHDIR) $(LIBRARIES); fi

clean:
	rm CascadingBackground
