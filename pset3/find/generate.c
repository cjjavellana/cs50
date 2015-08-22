/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Check the program argument's length.
    // Argument count must be between 2 and 3 only.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Convert argv[1] to integer.
    // This is the number of pseudorandom numbers to generate
    int n = atoi(argv[1]);

    // if the optional argument (seed) is given in the command line
    // use it to seed the srand48 function, otherwise seed it from 
    // time(NULL)
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // Generate the pseudorandom numbers and print in on screen
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
