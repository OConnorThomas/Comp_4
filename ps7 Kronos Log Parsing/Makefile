CC = g++
FLAGS = -g -Wall -Werror -pedantic -std=c++17
LIB = -lsfml-system
DEPS = LogParser.o

.PHONY: all clean lint

all: lint ps7 

ps7: main.o $(DEPS)
	$(CC) $(FLAGS) -o ps7 $^ $(LIB)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

lint:
	cpplint --recursive --quiet .

clean: 
	rm *.o ps7