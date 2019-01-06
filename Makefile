CC = gcc
CFLAGS = -Wall

OBJECTS = main.o dict.o

#main is used for testing purposes
main : $(OBJECTS)
	@echo "Linking object files..."
	$(CC) -o $@ $^

main.o : main.c
	@echo "Compiling main module..."
	$(CC) $(CFLAGS) -c $^

#dict.o is used for exporting as a library object file
dict : dict.c
	@echo "Creating object file without main..."
	$(CC) $(CFLAGS) -c $^

.PHONY : clean

clean:
	rm *.o