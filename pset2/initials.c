/**
 * Pset2 - Takes in a person's name and creates the person's initials
 *
 * Bit toggling operation taken from here:
 * http://bit.ly/1M3wS4E 
 *
 * @author - Christian Javellana
 */
#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define SPACE_CHAR 0x20

int main(void)
{
    string name;

    do
    {
        name = GetString();
    } while(strlen(name) < 1);

    for(int i = 0; i < strlen(name); i++)
    {
        // the first character or the character before is a space character
        if (i == 0 || ((int) *(name + i - 1)) == SPACE_CHAR)
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

