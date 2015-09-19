#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "stackcalc.h"

static void matrix_size(char *line, int *row, int *col);
static void matrix_readinput(Worksheet *w, char *file);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: spreadsheet <input file>\n");
        exit(1);
    }


    Worksheet *w = malloc(sizeof(Worksheet));
    //initWorksheet(w, 4, 4);
    //setValue(w, 0, 0, "A2");
    //printf("%s\n", getValue(w, 0, 0));

    matrix_readinput(w, argv[1]);
}

static void matrix_readinput(Worksheet *w, char *file)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Cant open input file\n");
        exit(1);
    }

    int colCounter = -1, rowCounter = 0;
    char *line;
    size_t read, len;
    while((read = getline(&line, &len, fp)) != -1)
    {
        if(colCounter == -1)
        {
            int r = 0, c = 0;

            // reads the matrix size from the
            // first line of the input file
            matrix_size(line, &r, &c);

            // initilizes the matrix of size r * c
            initWorksheet(w, r, c);
        } 
        else 
        {
            printf("[Setting Value] Row: %d, Col: %d, Content: %s\n", rowCounter, colCounter, line);
            setValue(w, rowCounter, colCounter, line);
            if (isCyclicRefError(w, rowCounter, colCounter))
            {
                printf("Cycling dependency starting at row: %d, col: %d\n", rowCounter, colCounter);
                exit(1);
            }
        }

        colCounter++;
        
        if (colCounter > 0 && (colCounter % w->cols) == 0)
        {
            colCounter = 0;
            rowCounter++;
        }
    }

    fclose(fp);
}

/**
 * Reads the matrix size given in the line and stores it in the 
 * row and col parameters
 */
static void matrix_size(char *line, int *row, int *col)
{
    char *token = strtok(line, " ");
    *col = atoi(token);

    token = strtok(NULL, " ");
    *row = atoi(token);
}

