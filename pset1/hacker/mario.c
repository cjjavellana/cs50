/*
 * mario.c - Pset1 hacker edition
 *
 */

#include <stdio.h>
#include <cs50.h>

#define HEIGHT_LOWER_LIMIT 0
#define HEIGHT_UPPER_LIMIT 23
#define GAP_WIDTH          2

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        height = GetInt();
    } while(height < HEIGHT_LOWER_LIMIT || height > HEIGHT_UPPER_LIMIT);

    for(int i = 0; i < height; i++)
    {
        // the base of the pyramid is twice the height with a 
        // gap of 2 spaces in between
        for(int j = 0; j < ((height * 2) + GAP_WIDTH); j++)
        {
            int printStart = height - i - 1;
            int printEnd = height + i + GAP_WIDTH;

            // print # when in the correct zone
            if (j >= printStart && j <= printEnd 
                    && j != height && j != (height + 1))
            {
                printf("#");
            }
            else if (j > printEnd)
            {
                break;
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
