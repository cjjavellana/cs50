#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

void partition(char *prefix, int n, int m);

int main(void)
{
    int n;

    do
    {
        printf("Enter a number: ");
        n = GetInt();
    }while(n < 0 || n > 30);

    for(int i = n; i > 0; i--)
    {
        int x = n - i;
        if (x == 0)
        {
            printf("%d\n", i);
        }
        else if(i == 1)
        {
            for(int j = 0; j < n; j++)
            {
                printf("1 ");
                if(j < n - 1)
                {
                    printf("+ ");
                }
            }
            printf("\n");
        }
        else 
        {
            int y = n - x;
            if (y >= x)
            {
                printf("%d + %d\n", y, x);
                
                //if x > 1, break it further down
                if(x > 1)
                {
                    char* prefix = malloc(sizeof(char) * 100);
                    sprintf(prefix, "%d + ", y);
                    partition(prefix, x, x - 1);
                    free(prefix);
                }
            }
            else
            {
                    char* prefix = malloc(sizeof(char) * 100);
                    sprintf(prefix, "%d + ", y);
                    partition(prefix, x, x - 1);
                    free(prefix);
            }
        }
    }
}

void partition(char* prefix, int n, int m)
{
    if(n == 1)
    {
        printf("%s\n", prefix);
        return;
    }
    
    char* new = malloc(sizeof(char) * 5);
    sprintf(new, "%d + %d + ", n - 1, m);
    strcat(prefix, new);
    free(new); //release temporary storage

    for(int i = n; i > 1; i--)
    {
        partition(prefix, n - 1, n - (n -1));
    }

}
