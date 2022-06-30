CC = gcc
CFLAGS = -g --std=c99 -Wall -Wpedantic

all:
	${CC} ${CFLAGS} brainfck.c -o bf

.PHONY: all
