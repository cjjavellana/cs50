#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *ch = malloc(sizeof(char) * 5);
    sprintf(ch, "%d ", 7);
    printf("CH: %s\n", ch);
    free(ch);
}
