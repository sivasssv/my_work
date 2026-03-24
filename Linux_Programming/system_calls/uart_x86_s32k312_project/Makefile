CC = gcc
CFLAGS = -o -wall
TARGET = uart_x86_S32
OBJECTS = main.o uart.o
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