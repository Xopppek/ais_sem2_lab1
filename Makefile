TARGET = lab1

CC = gcc
CFLAGS = -Wall -g

OBJ_DIR = obj
LIB_DIR = lib

SRC = main.c $(wildcard $(LIB_DIR)/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
