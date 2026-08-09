CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
SRCS = $(wildcard *.c)
TARGET = brobank

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -I. $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
