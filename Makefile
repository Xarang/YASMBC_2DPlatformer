CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -Isrc/include
VPATH=src
OBJS=input.o vector2.o map.o draw.o main.o entity.o foe_1.o foe_2.o player.o time_utils.o audio.o update.o list.o audio2.o free.o sprites.o block.o
LDLIBS= -lm

EXEC=main

CFLAGS += -g $(shell sdl2-config --cflags)

LDLIBS += $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer

all: $(EXEC)

check: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(EXEC): $(OBJS)

clean:
	$(RM) $(EXEC) $(OBJS)
