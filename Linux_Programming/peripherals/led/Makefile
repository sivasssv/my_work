# Makefile
CC=gcc
CFLAGS=-Wall -g
LIBS=-lgpiod
TARGET=toggle_gpio

all: $(TARGET)

$(TARGET): toggle_gpio.c
	$(CC) $(CFLAGS) -o $(TARGET) toggle_gpio.c $(LIBS)

clean:
	rm -f $(TARGET)
