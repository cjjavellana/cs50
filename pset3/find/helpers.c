/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

static bool binary_search(int value, int values[], int lower_bound, int upper_bound);
    
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    return binary_search(value, values, 0, n);
}

static bool binary_search(int value, int values[], int lower_bound, int upper_bound)
{
    int mid = ((upper_bound - lower_bound) / 2) + lower_bound;
    if (value == values[mid])
    {
        return true;
    }
        
    if (value < values[mid])
    {
        return binary_search(value, values, lower_bound, mid);
    }
    else if(value > values[mid])
    {
        return binary_search(value, values, mid, upper_bound);
    }

    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm

    for (int i = 0, k = 0; i < n; i++)
    {
        k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[k]) {
                k = j;
            }
        }

        if (k != i) 
        {
            int temp = values[k];
            values[k] = values[i];
            values[i] = temp;
        }
    }

    return;
}
