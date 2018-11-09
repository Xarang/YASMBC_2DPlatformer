CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
OBJS=src/vector2.o
LDLIBS=

CFLAGS += -I/usr/include/SDL2 -D_REENTRANT
LDLIBS += -L/usr/lib -pthread -lSDL2

all: $(OBJS)

clean:
	rm $(OBJS)
