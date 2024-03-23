.PHONY: all check clean

CC = gcc
CFLAGS = -std=gnu99 -Wall -g

OBJS = msh.o
EXEC = msh


all: $(OBJS)
	$(CC) $^ -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)
