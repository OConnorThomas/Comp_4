CC = g++
FLAGS = -Wall -Werror -pedantic -std=c++17
LIB = -lboost_unit_test_framework

.PHONY: all clean

all: ps1 test

ps1: main.o FibLFSR.o
	$(CC) $(FLAGS) -o ps1 $^ $(LIB)

test: test.o FibLFSR.o
	$(CC) $(FLAGS) -o test $^ $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) -c $<

clean: 
	rm *.o ps1 test