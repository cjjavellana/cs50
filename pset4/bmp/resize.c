/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

static void add_padding(int padding, FILE *fileptr);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // the scale
    int scale = atoi(argv[1]);

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // create the BITMAPFILEHEADER and BITMAPINFOHEADER structure 
    // for the outfile
    BITMAPFILEHEADER oBf;
    BITMAPINFOHEADER oBi;

    memcpy(&oBf, &bf, sizeof(BITMAPFILEHEADER));
    memcpy(&oBi, &bi, sizeof(BITMAPINFOHEADER));
   
    oBi.biWidth = bi.biWidth * scale;
    oBi.biHeight = bi.biHeight * scale;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine padding required for the out-file
    int oPadding = (4 - (oBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    oBi.biSizeImage = oBi.biWidth * abs(oBi.biHeight) * sizeof(RGBTRIPLE) + (oPadding * oBi.biHeight);

    oBf.bfSize = oBi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&oBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&oBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE *scanline = malloc(bi.biWidth * scale * sizeof(RGBTRIPLE));

        int byteCounter = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for(int k = 0; k < scale; k++)
            {
                memcpy(&scanline[byteCounter++], &triple, sizeof(RGBTRIPLE));
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        add_padding(oPadding, outptr); 

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        for (int j = 0; j < (scale - 1); j++)
        {
            fwrite(scanline, sizeof(RGBTRIPLE) * bi.biWidth * scale, 1, outptr);
            add_padding(oPadding, outptr); 
        }
        

        free(scanline);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

static void add_padding(int padding, FILE *fileptr)
{
    // then add it back (to demonstrate how)
    for (int k = 0; k < padding; k++)
    {
        fputc(0x00, fileptr);
    }
}
