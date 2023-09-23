CC ?= cc

.PHONY: all clean

all: Show

Show: Show.c
	$(CC) -std=c11 -g $< -o $@ -lncurses

clean:
	rm Show
