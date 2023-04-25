CC = g++
FLAGS = -g -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
DEPS = Checkers.o

.PHONY: all clean lint

all: lint Checkers

Checkers: main.o Checkers.o $(DEPS)
	$(CC) $(FLAGS) -o Checkers $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o Checkers