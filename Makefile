CC = g++
FLAGS = -std=c++11 -O3 -pedantic -lm
FILES = suftree.h main.cpp
PROG = lab5

lab5:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o lab5