#include <stdio.h>
#include <cs50.h>
#include <string.h>

/**
 * Pset2 - Takes in a person's name and creates the person's initials
 *
 * Bit toggling operation taken from here:
 * http://bit.ly/1M3wS4E 
 *
 */
int main(void)
{
    string name;

    do
    {
        name = GetString();
    } while(strlen(name) < 1);

    for(int i = 0; i < strlen(name); i++)
    {
        if (i == 0 || ((int) *(name + i - 1)) == 0x20)
        {
            // we know from Nate's shorts that the difference
            // between the lowercase & uppercase character is only a bit
            // so we'll do a bit flip
            int initial = (int) *(name + i);
            initial ^= (0 ^ initial) & (1 << 5);
            printf("%c", (char) initial);
        }
    }
    printf("\n");
    return 0;
}

