
all: snake

snake: main.c snake.c snake.h point.h pivot_point.h
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o snake main.c snake.c -I/usr/local/include -L/usr/local/lib/ -lpthread -lncurses -D _POSIX_C_SOURCE=200809L

clean:
	rm -f *.o a.out snake core
