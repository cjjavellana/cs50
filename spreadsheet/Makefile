
all: spreadsheet

spreadsheet: spreadsheet.c matrix.c matrix.h stackcalc.h regex.h regex.c commons.h commons.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o spreadsheet spreadsheet.c matrix.c regex.c commons.c -I/usr/local/include -L/usr/local/lib/ -lpcre2-8

test: matrix_test.c regex.c commons.c regex.h matrix.h
	clang -o matrixTest -ggdb3 -Wall -Werror -O0 -std=c99 -I/usr/local/include matrix_test.c matrix.c regex.c commons.c -L/usr/local/lib/ -lpcre2-8 -lcmocka

clean:
	rm -f *.o a.out spreadsheet core
