CC = gcc

dict: main.o dict.o
	$(CC) -o dict main.o dict.o

clean:
	rm *.o