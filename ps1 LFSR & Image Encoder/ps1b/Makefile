CC = g++
FLAGS = -Wall -Werror -pedantic -std=c++17
LIB = -lboost_unit_test_framework -lsfml-system -lsfml-graphics -lsfml-window
DEPS = FibLFSR.o

.PHONY: all clean

all: PhotoMagic test

PhotoMagic: PhotoMagic.o $(DEPS)
	$(CC) $(FLAGS) -o PhotoMagic $^ $(LIB)

test: test.o $(DEPS)
	$(CC) $(FLAGS) -o test $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

clean: 
	rm *.o PhotoMagic test