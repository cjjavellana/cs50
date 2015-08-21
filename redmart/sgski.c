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

typedef struct {
    char* solution;
    int distance;
    int drop;
} solution;

typedef struct {
    int row;
    int col;
} cellIndex;

// input file reading routines
void readfile(matrix *m, FILE* fp);
static void initMatrix(matrix *m, char* line);
static void readline(matrix *m, char* line, int rowIndex);

// solution finder
void findSkiPath(matrix *m, solution *sol);
static void checkAdjacentCells(char* path, matrix *m, cellIndex index, solution *sol, int currentValue);
void evaluateSolution(solution *sol, char* path);

// miscellaneous routines
void showContents(matrix *m);

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

void findSkiPath(matrix *m, solution *sol) {
    for (int i = 0; i < m->rowCount; i++) {
        for (int j = 0; j < m->colCount; j++) {
            int value = m->matrix[i][j];
            char* path = malloc(sizeof(char) * 50);
            sprintf(path, "%d ", value);
            
            cellIndex index;
            
            // check east
            index.row = i;
            index.col = j + 1;
            checkAdjacentCells(path, m, index, sol, value);

            // check west
            index.row = i;
            index.col = j - 1;
            checkAdjacentCells(path, m, index, sol, value);

            // check north 
            index.row = i - 1;
            index.col = j;
            checkAdjacentCells(path, m, index, sol, value);

            // check south
            index.row = i + 1;
            index.col = j;
            checkAdjacentCells(path, m, index, sol, value);
            
            free(path);
        }
    }    
}

static void checkAdjacentCells(char* path, matrix *m, cellIndex index, solution *sol, int currentValue) {

    // The base case - If we go beyond the limits of the matrix
    if(index.row < 0 || index.row > m->rowCount
            || index.col < 0 || index.col > m->colCount) {
        evaluateSolution(sol, path);
        return;
    }

    // check if the next cell has a lower value than the current cell
    int val = m->matrix[index.row][index.col];
    if(val < currentValue) {
        char *ch = malloc(sizeof(char) * 33);
        sprintf(ch, "%d ", val);
        strcat(path, ch);

        int r = index.row, c = index.col;

        // check east
        index.row = r;
        index.col = c + 1;
        checkAdjacentCells(path, m, index, sol, val);

        // check west
        index.row = r;
        index.col = c - 1;
        checkAdjacentCells(path, m, index, sol, val);

        // check north 
        index.row = r - 1;
        index.col = c;
        checkAdjacentCells(path, m, index, sol, val);

        // check south
        index.row = r + 1;
        index.col = c;
        checkAdjacentCells(path, m, index, sol, val);
    }

    // all ajacent cells have bigger value then the current cell
    evaluateSolution(sol, path);
    return;
}

/**
 * Checks if the longest path with the steepest drop has been found.
 */
void evaluateSolution(solution *sol, char* path) {

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
