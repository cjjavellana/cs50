#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/**
 * Converts the card number to string
 */
static char* asString(long long cardNumber);

/**
 * Returns AMEX if c is 34 or 37
 * Returns MASTERCARD if c is between 51 and 55 inclusive
 * Returns VIA if c is 4
 * Returns INVALID if c is neither of the above three.
 */
static char* getProvider(char* cardNumber);

#define VISA 4

int main(void)
{
    long long cardNumber;

    do
    {
        printf("Number: "); 
        cardNumber = GetLongLong(); 
    } while(cardNumber < 0);

    char *sCardNo = asString(cardNumber);
    int length = strlen(sCardNo);

    if (length < 13 || length > 16)
    {
        printf("INVALID\n");
    }
    else
    {
        int index = 0, checkSum = 0;

        // we start reading the individual digits from right to left
        // or from the least significant digit to the most significant
        // digit
        while(cardNumber)
        {
            int digit = cardNumber % 10;
            if ((index % 2) == 0)
            {
                checkSum += digit;
            }
            else
            {
                // if product exceeds 9, add the digits together
                int product = (digit << 1);                
                checkSum += (product > 9) ? (product % 10) + 1 : product;
            }
            cardNumber /= 10;
            index++;
        }

        int mod = checkSum % 10;
        if (mod)
        {
            printf("INVALID\n");
        }
        else
        {
            printf("%s\n", getProvider(sCardNo));
        }
        
        free(sCardNo);
    }
}

static char* asString(long long cardNumber)
{
    // allocate a buffer to hold the long long credit card number
    char *temp = malloc(sizeof(char) * 16);

    // convert the long long credit card number to string
    sprintf(temp, "%lld", cardNumber);
    return temp;
}

static char* getProvider(char* cardNumber)
{
    char buff[2];

    //take the first digit (or character) and assign to buff[0]
    buff[0] = *(cardNumber);
    buff[1] = '\0';

    // convert to integer & check if it is visa (card number starts with 4)
    int cardId = atoi(buff);
    if (cardId == VISA)
    {
        return "VISA";
    }

    // card is not visa, now we need to read the first two
    // digits of the credit
    sprintf(buff, "%c%c", *(cardNumber), *(cardNumber + 1));
    cardId = atoi(buff);

    if (cardId == 34 || cardId == 37)
    {
        return "AMEX";
    }

    if (cardId >= 51 && cardId <= 55)
    {
        return "MASTERCARD";
    }

    return "INVALID";
}
