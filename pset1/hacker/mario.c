#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        printf("Height: ");
        height = GetInt();
    } while(height < 0 || height > 23);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < ((height * 2) + 2); j++)
        {
            int printStart = height - i - 1;
            int printEnd = height + i + 2;

            if (j >= printStart && j <= printEnd && j != height && j != (height + 1))
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
