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
all: Mode7Demo

Mode7Demo:
	 then $(CC) $(CFLAGS) ./src/Mode7Demo.cpp -o Mode7Demo $(LIBRARIES); else $(CC) $(CFLAGS) ./src/Mode7Demo.cpp -o Mode7Demo $(SEARCHDIR) $(LIBRARIES); fi

clean:
	rm Mode7Demo
