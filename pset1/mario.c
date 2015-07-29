#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int height;

    do
    {
        printf("Height: ");
        height = GetInt();
        
    }while(height < 0 || height > 23);

    // outer loop for the half-pyramid's height
    for(int i = 0; i < height; i++)
    {
        // the bottom of the pyramid has height + 1 number 
        // of blocks
        for(int j = 0; j <= height; j++)
        {
            // we only print the hashes when column (j) 
            // is equal to height - row(i) - 1
            if (j >= height - i - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }
}
