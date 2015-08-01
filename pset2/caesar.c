#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Number of rotations is required. i.e ./caesar 13\n");
        return 1;
    }
    else
    {
        if(isdigit(*argv[1]))
        {
            int rotation = atoi(argv[1]);
            string plaintext = GetString();
            
            for(int i = 0; i < strlen(plaintext); i++)
            {
                if ((plaintext[i] >= 'a' && plaintext[i] <= 'z')
                        || (plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
                {
                    // Determine the value to be used to normalize
                    // since the formula (p + k) % 26 is applicable when
                    // a or A is 1, not when it's in ascii decimal
                    int n = islower(plaintext[i]) ? ('a' - 1) : ('A' - 1);

                    // perform the character substitution
                    int cipher = ((plaintext[i] - n) + rotation) % 26;

                    // restore back to ascii value and output to screen
                    printf("%c", cipher + n);
                }
                else
                {
                    // non-alphabet characters, display as it is
                    printf("%c", plaintext[i]);
                }
            }
            printf("\n");
        }
        else
        {
            printf("Invalid input. Enter a positive integer between 1 & 26\n");
            return 1;
        }
    }

    return 0;
}
