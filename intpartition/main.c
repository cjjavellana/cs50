#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//void partition(int n);
int partition(int left, int max, char *prefix);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./partition <p> \n");
        printf("Where:\n");
        printf("p - A positive integer that you want to get the partition of\n");
    }
   
    int n = atoi(argv[1]), max = n;
    char prefix[255];
    memset(prefix, '\0', sizeof(prefix));
    while(max > 0) 
    {    
        int p = n - max;
        int temp_max = (max > p) ? p : max;
        do
        {
            sprintf(prefix, "%s %d", prefix, max);
            partition(p, temp_max, prefix);
            printf("%s\n", prefix);
            memset(prefix, '\0', sizeof(prefix));
        } while(--temp_max > 0 && p > 1);
        
        
        max--;            
    }
    return 0;
}

int partition(int left, int max, char *prefix)
{    
    if(left == 0)
    {
        return 0;
    }
    else
    {
        sprintf(prefix, "%s %d", prefix, max);
        int n = left - max;
        
        max = (max > n) ? n : max;
        return partition(n, max, prefix);
    }
}
