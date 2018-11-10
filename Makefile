CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -Isrc/include
VPATH=src
OBJS=input.o vector2.o map.o draw.o main.o
LDLIBS= 

EXEC=main

CFLAGS += -g

LDLIBS += -lSDL2 -lSDL2_image 

all: $(EXEC)

check: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(EXEC): $(OBJS)

clean:
	$(RM) $(EXEC) $(OBJS)
