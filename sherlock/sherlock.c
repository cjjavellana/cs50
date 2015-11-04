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
        char *digits = malloc(sizeof(char) * n + 1);
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
