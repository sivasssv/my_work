CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = project
OBJECTS = main.o string.o
all:$(OBJECTS)
	@echo  "Building...."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) 

*.o: *.c
	@echo  "creating objects...."
	$(CC) -c $*.c

clean:
	@echo  "Cleaning...."
	rm -rf *.o
	rm $(TARGET)
