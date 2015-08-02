#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Specify the encryption key. i.e. ./vigenere bacon\n");
        return 1;
    }

    string key = argv[1];              // the encryption key
    int keyLength = strlen(key);        // the length of the key
    int nKey[keyLength -1];             // the array containing the normalized keys

    for(int i = 0; i < keyLength; i++)
    {
        if (isalpha(key[i]))
        {
            nKey[i] = tolower(key[i]) - 'a';
        }
        else
        {
            printf("Invalid key. Only a-z and A-Z are allowed\n");
            return 1;
        }
    }

    string plaintext = GetString();     // the plaintext to encrypt

    int keyIndex = 0;
    for(int i = 0; i < strlen(plaintext); i++)
    {
        if ((plaintext[i] >= 'a' && plaintext[i] <= 'z') 
                || (plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
        {
            int subtractor = islower(plaintext[i]) ? 'a' : 'A';
            int cipherChar = (plaintext[i] - subtractor + nKey[keyIndex]) % 26;
            printf("%c", cipherChar + subtractor);
            keyIndex++;
            if (keyIndex == keyLength)
            {
                keyIndex = 0;
            }
        }
        else 
        {
            printf("%c", plaintext[i]); 
        }
    }
    printf("\n");

    return 0;
}
