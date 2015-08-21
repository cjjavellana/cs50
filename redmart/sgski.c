// required; otherwise clang will complain that getline has not been declared
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int **matrix;
    int rowCount;
    int colCount;
} matrix;

static void initMatrix(matrix *m, char* line);
static void readline(matrix *m, char* line, int rowIndex);

void showContents(matrix *m);
void readfile(matrix *m, FILE* fp);

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

    matrix *m = malloc(sizeof(matrix));

    // read the input file into the matrix
    readfile(m, ifp);
    printf("Row Size: %d, Col Size: %d\n", m->rowCount, m->colCount);
    showContents(m);
    
    // release resources
    free(m);
    fclose(ifp);

    return 0;
}

void readfile(matrix *m, FILE* fp) {
    int rowIndex = 0;
    size_t len = 0;
    size_t read;
    char *line;
    
    while ((read = getline(&line, &len, fp) != -1)) {
        if (rowIndex == 0) {
            // the first row of the input file
            // contains the size of the matrix.
            initMatrix(m, line);
        } else {
            readline(m, line, rowIndex);
        }

        rowIndex++;
    }
}

/**
 * Reads the size of the matrix from the first line of the input file and 
 * sets the row and column counts into the parameters rowCount and colCount 
 * attributes of matrix m.
 *
 * This function is to be called on the first line of the input file.
 */
static void initMatrix(matrix *m, char* line) {

    // reads the row count - the first value on the line string
    char *ch = strtok(line, " ");
    m->rowCount = atoi(ch);
    
    // reads the column count - the second value on the line string
    ch = strtok(NULL, " ");
    m->colCount = atoi(ch);
      
    // initialize a two-dimentional array of size rowCount * columnCount
    int** matrix = (int **) malloc(sizeof(int *) * m->rowCount);
    for(int i = 0; i < m->rowCount; i++) {
       matrix[i] = (int *) malloc(sizeof(int) * m->colCount); 
    }
   
    m->matrix = matrix;    
}

static void readline(matrix *m, char* line, int rowIndex) {
    int colIndex = 0;
    char *ch = strtok(line, " ");

    while(ch != NULL) {
        m->matrix[rowIndex - 1][colIndex] = atoi(ch);
        ch = strtok(NULL, " ");
        colIndex++;
    }
}

/**
 * Prints the contents of the matrix into the console
 */
void showContents(matrix *m) {
    for(int i = 0; i < m->rowCount; i++) {
        for (int j = 0; j < m->colCount; j++) {
            printf("%d ", m->matrix[i][j]);
        }
        printf("\n");
    }
}
