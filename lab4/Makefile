CC = gcc
CFLAGS = -pedantic -Wall -std=c99 -Werror -Wno-sign-compare -lm

all:  
	$(CC) $(CFLAGS) main.c -o lab
clean:
	rm -f *.o lab
tar:
	rm -f *.o lab
	cd ..
	tar -cf lab.tar ./lab
