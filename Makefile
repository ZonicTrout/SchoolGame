CC = clang++
source = $(wildcard src/*.c*)
LIB = -lSDL2 -lSDL2_image -Iresources -Iinclude
NOWARN_FLAGS = $(LIB)
FLAGS = -Wall -Wextra $(LIB) 
EXEC = game

compile = $(CC) $(source) -o $(EXEC)

all:
	$(compile) $(FLAGS)

noWarn:
	$(compile) $(NOWARN_FLAGS)

run:
	$(compile) $(NOWARN_FLAGS)
	./$(EXEC)

