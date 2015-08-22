#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "sort.h"

int search(int value, int values[]);

void printValues(const int values[], int arraySize);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Invalid input. Please enter array values i.e. ./binarysearch 10 7 8 9 25\n");
        return -1;
    }

    int dateSetLength = argc - 1;
    int values[dateSetLength];

    for(int i = 1; i < argc; i++)
    {
       values[i - 1] = atoi(argv[i]); 
    }
    
    printf("Before Sort\n");
    printValues(values, dateSetLength); 
   
    //bubbleSort(values, dateSetLength);
    selectionSort(values, dateSetLength);
    printf("After Sort\n");
    printValues(values, dateSetLength); 

    return 0;
}

void printValues(const int values[], int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        printf("%d ", values[i]);
    }
    printf("\n");
}
