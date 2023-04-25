CC = g++
FLAGS = -g -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system
DEPS = RandWriter.o

.PHONY: all clean lint

all: lint TextWriter test

TextWriter: TextWriter.o RandWriter.o $(DEPS)
	$(CC) $(FLAGS) -o TextWriter $^ $(LIB)

test: test.o RandWriter.o $(DEPS)
	$(CC) $(FLAGS) -o test $^ $(LIB) -lboost_unit_test_framework

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o TextWriter test output.txt