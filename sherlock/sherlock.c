#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

void find_digits(int n, char* digits);

int main(int argc, char* argv[]) {

    char *line = NULL;
    size_t size = 0;

    getline(&line, &size, stdin);
    int testCaseCount = atoi(line);
    for(int i = 0; i < testCaseCount; i++) {
        getline(&line, &size, stdin);
        
        int n = atoi(line);
        char *digits = malloc(sizeof(char) * (n * 2) + 1);
        memset(digits, 0, n + 1);

        find_digits(n, digits);
        if(n == strlen(digits)) {
            printf("%s\n", digits);
        } else {
            printf("-1\n");
        }
    
        free(digits);
    }

    return 0;
}

void find_digits(int n, char* digits) {

    char *threes = malloc(sizeof(char) * n + 1);
    char *fives = malloc(sizeof(char) * n + 1);
    memset(threes, 0, n + 1);
    memset(fives, 0, n + 1);
    
    while (n >= 3) {

        if((n % 3) == 0) {
            char *tmp = malloc(sizeof(char) * n + 1);
            memset(tmp, 0x35, n);
            tmp[n] = '\0';
            strcat(fives, tmp);
            free(tmp);
            break;
        }

        if((n % 5) == 0) {
            strcat(threes, "33333");
            n -= 5;
            continue;
        }
    
        if (n > 3) {
            strcat(fives, "555");
            n -= 3;
            continue;
        }  
    }

    strcat(digits, fives);
    strcat(digits, threes);

    free(threes);
    free(fives);
}
