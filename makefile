CC = gcc
flags = -Wall -g -o

dict: main.o dict.o
	$(CC) $(flags) dict main.o dict.o

clean:
	rm *.o