#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void bruteForce(char *cipherText);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack <ciphertext>");
        exit(EXIT_FAILURE);
    }

    // Check a dictionary hash for common words and passwords

    char *grepQuery = malloc(sizeof(char) * 100);
    strcat(grepQuery, "/bin/grep \"");
    strcat(grepQuery, argv[1]);
    strcat(grepQuery, "\"");
    strcat(grepQuery, " *.txt");

    FILE *dictionary = popen(grepQuery, "r");
    if (dictionary == NULL)
    {
        printf("Unable to run command\n");
        exit(EXIT_FAILURE);
    }

    char queryResult[300];

    if (fgets(queryResult, sizeof(queryResult) - 1, dictionary) != NULL)
    {
        // queryResult is in the grep output format:
        // <filename>:<plaintext>=<encrypted value)
        char *plainText = strtok(queryResult, "=:");
        while (plainText != NULL)
        {
            plainText = strtok(NULL, "=:");
            printf("%s\n", plainText);
            break;
        }
    } 
    else 
    {
        // we are not able to find a password in the dictionary hash
        // how about brute forcing...
        bruteForce(argv[1]);
    }

    pclose(dictionary);

    return 0;
}
   

void bruteForce(char *cipherText)
{
    int len = 1;
    int maxChar = 8;
    char *encrypted = NULL;
    char *salt = malloc(sizeof(char) * 3);

    // copy the first 2 characters from the cipherText
    strncpy(salt, cipherText, 2);   
    // manually add string terminator
    strcat(salt, "\0");             

    while(len <= maxChar)
    {
        // initialize guess
        // +1 for the null terminator 
        char *guess = malloc(sizeof(char) * (len + 1));         
        char *finalState = malloc(sizeof(char) * (len + 1));

        // we start from '!' or 0x21 and we end at '~' or 0x7e
        // refer to the ascii table at http://www.asciitable.com/
        for(int i = 0; i < len; i++)
        {
            *(guess + i) = (char) 0x21; 
            *(finalState + i) = (char) 0x7E;
        }
        *(guess + len) = '\0';
        *(finalState + len) = '\0';

        // do until we've exhausted all possible combinations
        // of 0x21 "!" to 0x7E ("~") for the length of the key len
        while(strcmp(guess, finalState) != 0)
        {
            // increment the last character
            int charIndex = len - 1; 
            for(int nextChar = 0x21; nextChar < 0x7F; nextChar++)
            {
                *(guess + charIndex) = nextChar;

                printf("Testing Out: %s; Salt: %s\n", guess, salt);

                // Encrypt plaintext guess and 
                // check if it matches our ciphertext
                encrypted = crypt(guess, salt);
                if (strcmp(encrypted, cipherText) == 0)
                {
                    printf("%s\n", guess);
                    return; 
                }
            }

            // increment the character(s) before the last
            int idx = charIndex - 1;
            while(idx >= 0)
            {
                *(guess + idx) = *(guess + idx) + 1;

                // if last character exceeded '~', increment the 
                // character before it
                if (*(guess + idx) > 0x7E)
                {
                    // reset last character back to 0x21 "!"
                    // and increment the character before 
                    // it until we've reached start of guess
                    *(guess + idx) = 0x21;
                    idx--;
                }
                else
                {
                    break;
                }
            }
        }

        len++;

        // clean up resources
        free(guess);
        free(finalState);
    }

    return;
}
