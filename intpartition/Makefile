all: partition

partition: main.c
		clang -ggdb3 -O0 -std=c99 -Wall -Werror -o partition main.c

clean:
	rm -f *.o core partition
