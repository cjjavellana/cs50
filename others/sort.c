#include <stdlib.h>
#include "sort.h"

//static int isSorted(int *iArray, int arraySize);

void bubbleSort(int *iArray, int arraySize)
{
    while(arraySize > 0)
    {
        for(int i = 0; i < arraySize - 1; i++)
        {
            if(*(iArray + i) > *(iArray + i + 1))
            {
                int temp = *(iArray + i);
                *(iArray + i) = *(iArray + i + 1);
                *(iArray + i + 1) = temp;
            }
        }
        arraySize--;
    }
}

void selectionSort(int *iArray, int arraySize)
{

}

void insertionSort(int *iArray, int arraySize)
{

}

void mergeSort(int *iArray, int arraySize)
{

}

void quickSort(int *iArray, int arraySize)
{

}

/**
static int isSorted(int *iArray, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        if(*(iArray + i) > *(iArray + i + 1))
        {
            return 0;
       }
    }

    return 1;
}
**/

