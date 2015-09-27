#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
static void closeFile(FILE *fileptr);

int main(int argc, char* argv[])
{
    char *infile = "card.raw";
    FILE *fileptr = fopen(infile, "r");
    if (fileptr == NULL)
    {
        printf("Unable to open %s\n", infile);
        exit(1);
    }

    uint8_t data[512];
    size_t read = 0;
    int ctr = 0;

    FILE *outptr = NULL;
    while((read = fread(&data, 512, 1, fileptr)) != -1)
    {
        if (feof(fileptr))
        {
            break;
        }

        if ((data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && data[3] == 0xe0)
            || (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && data[3] == 0xe1))
        {
            // we have encountered another file, close the previous one
            closeFile(outptr);

            // open a new file
            char filename[16];
            sprintf(filename, "%03d.jpg", ctr);
            outptr = fopen(filename, "w");

            ctr++;
        }

        // write bytes to out file
        if (outptr != NULL)
        {
            fwrite(&data, 512, 1, outptr);
        }
    }

    closeFile(outptr);
    fclose(fileptr);

    return 0;
}

static void closeFile(FILE *fileptr)
{
    if (fileptr != NULL)
    {
        fclose(fileptr);
    }
}
