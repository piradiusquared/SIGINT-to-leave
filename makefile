CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g

.DEFAULT_TARGET = ALL
ALL: sigint
sigint: sigint.c

clean:
	rm -f sigint *.o