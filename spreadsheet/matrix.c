#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pcre2.h>

#include "regex.h"
#include "matrix.h"
#include "commons.h"

// ~ Static function propotypes ==================
static int isCyclicError(const Worksheet *worksheet, const char *visitedCells, CellReference *cellReference);

/**
 * Initializes the worksheet cells of size rows * columns. 
 *
 * Returns 0 if an error is encountered.
 */
int initWorksheet(Worksheet *worksheet, int rows, int columns) {
    worksheet->rows = rows;
    worksheet->cols = columns;

    char ***matrix = (char ***) malloc(sizeof(char **) * rows);
    for(int i = 0; i < rows; i++) {
        matrix[i] = (char **) malloc(sizeof(char *) * columns);

        for(int j = 0; j < columns; j++) {
            matrix[i][j] = (char *) malloc(sizeof(char) * CELL_CONTENT_LIMIT);
        }
    }

    worksheet->cells = matrix;
    return 1;
}

/**
 * Sets s to the worksheet cell at row, column.
 *
 * Returns 0 if strlen(s) > CELL_CONTENT_LIMIT 
 */
int setValue(Worksheet *worksheet, int row, int column, char* s) {
    if (strlen(s) <= CELL_CONTENT_LIMIT) {
        strncpy(worksheet->cells[row][column], s, strlen(s));
        return 1;
    } else {
        return 0;
    }
}

/**
 * Returns the value at row, col
 */
char* getValue(const Worksheet *worksheet, int row, int column) {
    return worksheet->cells[row][column];
}


/**
 * Converts the given location (row, column) to a spreadsheet cell reference i.e. A1
 */
CellReference *convertToCellReference(const MatrixLocation *location)
{
    CellReference *ref = malloc(sizeof(CellReference));

    char rowRef[2];
    rowRef[0] = (char) (location->row + ROW_TO_ASCII_OFFSET);
    rowRef[1] = '\0';

    char *colRef = malloc(sizeof(char) * getNumberOfDigits(location->col) + 1);
    sprintf(colRef, "%d", location->col + 1);
    strcat(colRef, "\0");

    ref->cellReference = malloc(1 + strlen(colRef) + 1);
    sprintf(ref->cellReference, "%s%s", rowRef, colRef);
    free(colRef);

    return ref;
}

/**
 * Returns a pointer to a MatrixLocation structure
 */
MatrixLocation *convertToMatrixLocation(const CellReference *ref)
{
    MatrixLocation *loc = malloc(sizeof(MatrixLocation));
    loc->row = ((int) toupper(ref->cellReference[0])) - ROW_TO_ASCII_OFFSET;

    char *col = malloc(sizeof(char) + strlen(ref->cellReference));
    col = strncpy(col, ref->cellReference + 1, strlen(ref->cellReference) - 1);
    loc->col = atoi(col) - 1;
    return loc;
}

/**
 * Checks if a given formula at row, col refers to some cells which themselves
 * refer back to row,col
 *
 * Returns 0 if an error is encountered.
 */
int isCyclicRefError(const Worksheet *worksheet, int row, int col)
{
    MatrixLocation m = { row, col };
    CellReference *cellRef = convertToCellReference(&m);
    return isCyclicError(worksheet, "", cellRef);
}

/**
 * An internal function for checking cyclic reference dependency error.
 *
 * ==========
 * Returns 1 if cyclic dependency is found, 0 if otherwise
 */
static int isCyclicError(const Worksheet *worksheet, const char *visitedCells, CellReference *cellRef)
{
    pcre2_match_data *match_data = NULL;
    int rc = 0;

    MatrixLocation *m = convertToMatrixLocation(cellRef);  
    char *cellValue = getValue(worksheet, m->row, m->col);
    free(m);

    char *token = strtok(cellValue, " ");
    pcre2_code *re = getCellReferencePattern();
    while(token != NULL)
    {
        match_data = pcre2_match_data_create(20, NULL);
        int subjectLength = strlen(token);
        rc = pcre2_match(re, (PCRE2_SPTR) token, subjectLength, 0, 0, match_data, NULL); 
        
        if (rc > 0)
        {
            printf("Token Found: %s\n", token);
            // search if current cellref is in the visited cells
            pcre2_code *searchVal = compilePattern(token);
            int isCyclicDependency = pcre2_match(searchVal, (PCRE2_SPTR) visitedCells, strlen(visitedCells), 0, 0, match_data, NULL);
            if (isCyclicDependency > 0)
            {
                free(searchVal);
                free(re);
                return 1;
            }
        }

        //length of existing visitedCells + space character + length of cellRef to be appended + null terminator
        char *newVisitedCells = malloc(sizeof(char) * (strlen(visitedCells) + 1 + strlen(cellRef->cellReference)) + 1);
        strcpy(newVisitedCells, visitedCells);
        strcat(newVisitedCells, " ");
        strcat(newVisitedCells, cellRef->cellReference);
        
        CellReference *tokenCellRef = malloc(sizeof(CellReference));
        tokenCellRef->cellReference = token;

        if(isCyclicError(worksheet, (const char *) newVisitedCells, tokenCellRef))
        {        
            free(newVisitedCells);
            free(cellRef);
            free(re);
            return 1;
        }
       
        free(newVisitedCells);
        free(tokenCellRef);
        free(cellRef);
        token = strtok(NULL, " ");
    }

    free(token);
    free(re);
    return 0;
}

