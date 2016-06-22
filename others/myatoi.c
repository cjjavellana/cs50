#include <string.h>
#include <stdio.h>

#define ASCII_ZERO 48

int atoi(char *s);
int digits2(char s);

int main(int argc, char *argv[]) {
    printf("%i\n", atoi(argv[1]));
}

int atoi(char *s) {
    if (s == NULL) return 0;
    
    int len = strlen(s);
    if (len == 0) return 0;

    int multiplier = 1;
    int returnValue = 0;
    for(int i = len - 1; i >= 0; i--) {
        int digit = digits2(s[i]);
        if (digit == -1) {
            return 0;
        }
        returnValue += digit * multiplier;  
        multiplier *= 10;
    }

    return returnValue;
}

int digits2(char s) {
    int ascii = (int) s - ASCII_ZERO;
    if (ascii < 0 || ascii > 9) return -1;
    return ascii;
}
