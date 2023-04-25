CC = g++
FLAGS = -g -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system
DEPS = EDistance.o

.PHONY: all clean lint

all: lint EDistance

EDistance: main.o EDistance.o $(DEPS)
	$(CC) $(FLAGS) -o EDistance $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o EDistance