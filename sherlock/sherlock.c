#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

void find_digits(int n, char* digits);

int main(int argc, char* argv[]) {

    int line_no = 0, testcases = 0, char_counter = 0;
    char buff[100];
    memset(buff, 0, 100);
    char ch;

    while(read(0, &ch, 1) > 0) {
        if(ch == '\n') {
            if(line_no == 0) {
                testcases = atoi(buff);
            } else {
                char *digits = malloc(sizeof(char) * 100 + 1);
                memset(digits, 0, 101);

                int n = atoi(buff);
                find_digits(n, digits);
                if(n == strlen(digits)) {
                    printf("%s\n", digits);
                } else {
                    printf("-1\n");
                }
    
                free(digits);
            }
            line_no++;
            char_counter = 0;
            memset(buff, 0, 100);
        } else {
            buff[char_counter++] = ch;
        }       
    }

    return 0;
}

void find_digits(int n, char* digits) {

    if((n % 3) == 0) {
        for(int i = 0; i < n; i++) {
           strcat(digits, "5");
        }
        return;
    }

    if((n % 5) == 0) {
        for(int i = 0; i < n; i++) {
           strcat(digits, "3");
        }
        return;
    }

    if (n > 3) {
        strcat(digits, "555");
        find_digits(n - 3, digits);
    }

    return;
}
