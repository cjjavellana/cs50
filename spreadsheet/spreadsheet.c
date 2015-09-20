#define _XOPEN_SOURCE 700
#define PCRE2_CODE_UNIT_WIDTH 8

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <pcre2.h>

#include "regex.h"
#include "matrix.h"
#include "stackcalc.h"

static void matrix_size(char *line, int *row, int *col);
static void matrix_readinput(Worksheet *w, char *file);
static void matrix_evaluate_worksheet(Worksheet *w);
static double matrix_evaluate_expression(const Worksheet *w, char *expression, int row, int col);
static int matrix_is_operator(char *val);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: spreadsheet <input file>\n");
        exit(1);
    }

    Worksheet *w = malloc(sizeof(Worksheet));
    matrix_readinput(w, argv[1]);
    matrix_evaluate_worksheet(w);
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

static void matrix_evaluate_worksheet(Worksheet *w)
{
    for(int i = 0; i < w->rows; i++)
    {
        for(int j = 0; j< w->cols; j++)
        {
            char *expression = getValue(w, i, j);
            double d = matrix_evaluate_expression(w, expression, i, j);
            printf("Row: %d; Col: %d; Value: %.5f\n", i, j, d);
        }
    }
}

static double matrix_evaluate_expression(const Worksheet *w, char *expression, int row, int col)
{
    Stack *stack = malloc(sizeof(Stack));
    pcre2_match_data *match_data = NULL;
    int rc = 0;
    pcre2_code *re = getCellReferencePattern();

    char *token = malloc(sizeof(char) * strlen(expression) + 1);
    strcpy(token, expression);
    token[strlen(token) - 1] = '\0';
    token = strtok(token , " ");

    while(token != NULL)
    {
        match_data = pcre2_match_data_create(20, NULL);
        int len = strlen(token);
        rc = pcre2_match(re, (PCRE2_SPTR) token, len, 0, 0, match_data, NULL); 
        if (rc > 0)
        {
            CellReference cellRef = { token };
            MatrixLocation *loc = convertToMatrixLocation(&cellRef);

            char *cellExpression = getValue(w, loc->row, loc->col);
            char *duplicateExpr = malloc(sizeof(char) * strlen(cellExpression));
            strcpy(duplicateExpr, cellExpression);

            double result = matrix_evaluate_expression(w, duplicateExpr, loc->row, loc->col);

            Node *node = malloc(sizeof(Node));
            node->value = result;
            push(stack, node);

            free(duplicateExpr);
        }
        else
        {
            if (matrix_is_operator(token))
            {
                Node *op1 = pop(stack);
                Node *op2 = pop(stack);

                double val1 = op1->value;
                double val2 = op2->value;
                
                double result = 0.0;
                
                if (strcmp(token, "+") == 0) result = val1 + val2;
                if (strcmp(token, "-") == 0) result = val2 - val1;
                if (strcmp(token, "*") == 0) result = val1 * val2;
                if (strcmp(token, "/") == 0)  result = val2 / val1;

                Node *newValue = malloc(sizeof(Node));
                newValue->value = result;
                push(stack, newValue);
            }
            else 
            {
                Node *newValue = malloc(sizeof(Node));
                newValue->value = atoi(token);
                push(stack, newValue);
            }
        }

        token = strtok(NULL, " ");
    }

    Node *node = pop(stack);
    double retVal = node->value;

    free(stack);
    free(node);
    free(token);

    return retVal;
}

static int matrix_is_operator(char *val)
{
    if (strcmp(val, "+") == 0 ||
            strcmp(val, "-") == 0 ||
            strcmp(val, "*") == 0 ||
            strcmp(val, "/") == 0)
    {
        return 1;
    }

    return 0;
}

