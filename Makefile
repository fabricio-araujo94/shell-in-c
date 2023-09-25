CC = gcc
CFLAGS = -g -Wall -Wextra -Wno-unused-result

all: main

main: main.c

clean:
	rm -f *~ $(ALL)
