#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

static int** initMatrix(char*, int*, int*);

static int** readfile(int*, int*, FILE*);

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("usage: sgski <input file>\n");
        exit(1);
    }

    char* filename = argv[1];
    FILE *ifp = fopen(filename, "r");
    if (ifp == NULL) {
        printf("Unable to open input file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int *colCount = malloc(sizeof(int));
    int *rowCount = malloc(sizeof(int));

    readfile(colCount, rowCount, ifp);

    free(colCount);
    free(rowCount);
    fclose(ifp);

    return 0;
}

static int** readfile(int* colCount, int* rowCount, FILE* fp) {
    int isFirstRow = 1;
    size_t len = 0;
    size_t read;
    char *line;
    
    int **matrix = NULL;
    
    while ((read = getline(&line, &len, fp) != -1)) {
        if (isFirstRow) {
            // the first row of the input file
            // contains the size of the matrix.
            matrix = initMatrix(line, rowCount, colCount);
            isFirstRow = 0;
        } else {

        }
    }
    
    return matrix;
}

/**
 * Reads the size of the matrix from the first line of the input file and 
 * sets the row and column counts into the parameters *rowCount and *colCount.
 * 
 * This function returns a two-dimentional array of size rowCount * colCount.
 *
 * This function is to be called on the first line of the input file.
 *
 * Ensure to free() the matrix after use.
 */
static int** initMatrix(char* line, int* rowCount, int* colCount) {
    // reads the row count - the first value on the line string
    char *ch = strtok(line, " ");
    *rowCount = atoi(ch);
    
    // reads the column count - the second value on the line string
    ch = strtok(NULL, " ");
    *colCount = atoi(ch);
      
    // initialize a two-dimentional array of size rowCount * columnCount
    int** matrix = (int **) malloc(sizeof(int *) * *rowCount);
    for(int i = 0; i < *rowCount; i++) {
       matrix[i] = (int *) malloc(sizeof(int) * *colCount); 
    }
    
    return matrix;
}
