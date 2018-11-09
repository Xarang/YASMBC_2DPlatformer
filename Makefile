CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
OBJS=src/vector2.o

all: $(OBJS)

clean:
	rm $(OBJS)
