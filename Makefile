.PHONY: all clean

CC= gcc
all:a.out
a.out:main.c ctx.h ctx.c
	$(CC) -o $@ $^

clean:
	rm -rf a.out
