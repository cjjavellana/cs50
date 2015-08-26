#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    char *plaintext;
    char *encrypted;
} keypair;

void convertToUpper(char *str);

int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        printf("Usage: ./pwdgenerator password_file salt\n");
        exit(EXIT_FAILURE);
    }

    char *pwdFile = argv[1];
    char *salt = argv[2];
    FILE *fp = fopen(pwdFile, "r");
    char *word;
    size_t len = 0, read;

    while((read = getline(&word, &len, fp)) != -1)
    {
        *(word + (strlen(word) - 1)) = '\0';
        if(strlen(word) < 10)
        {
            //convertToUpper(word);
            char *pwd = crypt(word, salt);
            printf("%s=%s\n", word, pwd);
        }
    }

    fclose(fp);
}

void convertToUpper(char *str)
{
    do
    {
        *str = toupper(*str);
    } while(*str++);
}

