CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -Isrc/include
VPATH=src
OBJS=main.o input.o vector2.o map.o draw.o
LDLIBS=

EXEC=main

CFLAGS += -g

LDLIBS += -lSDL2

all: $(EXEC)

$(EXEC): $(OBJS)

clean:
	$(RM) $(EXEC) $(OBJS)
