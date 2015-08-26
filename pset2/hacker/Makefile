all: pwdgenerate crack

pwdgenerate: pwdgenerator.c
				clang -ggdb3 -O0 -std=c99 -Wall -Werror -o pwdgenerator pwdgenerator.c -lcrypt

crack: crack.c
		clang -ggdb3 -O0 -std=c99 -Wall -Werror -o crack crack.c -lcrypt

clean:
	rm -f *.o core pwdgenerator crack
