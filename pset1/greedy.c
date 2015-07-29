#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float owed;
    
    printf("O hai! ");

    do 
    {
        printf("How much change is owed?\n");
        owed = GetFloat();
    } while(owed < 0);

    // multiply as float first before rounding off 
    // to neareast int
    int n = round(owed * 100.0);

    // nTotalCoins represents the number of coins 
    // owed coins
    int nTotalCoins = 0;

    while(n > 0)
    {
        // div represents the divisor for the current
        // iteration
        int div = 0;

        if (n >= 25) 
        {
            div = 25;
        }
        else if(n >= 10) 
        {
            div = 10;
        }
        else if(n >= 5) 
        {
            div = 5;
        }
        else if(n >= 1) 
        {
            div = 1;
        }
       
        // nCoins represents the number of coins 
        // in the current iteration
        int nCoins = n / div;

        nTotalCoins += nCoins;
        n -= (div * nCoins);
    }

    printf("%i\n", nTotalCoins);
    return 0;
}

