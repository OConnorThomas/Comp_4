CC = g++
FLAGS = -g -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system -lsfml-graphics -lsfml-window
DEPS = PTree.o

.PHONY: all clean lint

all: lint PTree

PTree: main.o PTree.o $(DEPS)
	$(CC) $(FLAGS) -o PTree $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o PTree