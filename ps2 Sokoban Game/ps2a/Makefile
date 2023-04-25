CC = g++
FLAGS = -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system -lsfml-graphics -lsfml-window
DEPS = Sokoban.o

.PHONY: all clean lint

all: lint Sokoban

Sokoban: main.o Sokoban.o $(DEPS)
	$(CC) $(FLAGS) -o Sokoban $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o Sokoban