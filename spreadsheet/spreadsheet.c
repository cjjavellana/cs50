#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "stackcalc.h"

int main(int argc, char *argv[])
{
    Worksheet *w = malloc(sizeof(Worksheet));
    initWorksheet(w, 4, 4);
    setValue(w, 0, 0, "A2");
    printf("%s\n", getValue(w, 0, 0));
}
