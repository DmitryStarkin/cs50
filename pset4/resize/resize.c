/**
 * resize.c
 *
 * 
 *
 * resizes a BMP  just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale(integer<100) infile outfile\n");
        return 1;
    }

    // remember filenames and scale
    int scale;
    char trach;
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (sscanf(argv[1], " %i %c", &scale, &trach) != 1) {
        fprintf(stderr, "Usage: ./resize scale(integer<100) infile outfile\n");
        return 1;
    }
    if (scale < 1 | scale > 100) {
        fprintf(stderr, "Usage: ./resize scale(integer<100) infile outfile\n");
        return 1;   
    }
        
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr,"Could not open %s.\n", infile);
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

    //initialise filesize for outfile
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
   
    //scip header
    fseek(outptr, bf.bfSize, SEEK_SET);
    
    // determine padding for scanlines
    int padding_input =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out =  (4 - (bi.biWidth*scale* sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
    
        // multiple out scanlines
        for (int y=0; y<scale; y++) { 
            if (y) {
            
                //return to begin of scanline
                fseek(inptr, -bi.biWidth*sizeof(RGBTRIPLE), SEEK_CUR);
            }
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++){
                
                    // temporary storage
                    RGBTRIPLE triple;
                    
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                    // multiple out triple
                        for (int z=0; z<scale; z++) {
                        
                            // write RGB triple to outfile
                            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                            
                            //update outfilesize
                            bf.bfSize=bf.bfSize+sizeof(RGBTRIPLE);
                        } 
                }
        
                // add padding back (to demonstrate how)
                for (int k = 0; k < padding_out; k++){
                    fputc(0x00, outptr);
                    
                    //update outfilesize
                    bf.bfSize=bf.bfSize+sizeof(char);
                }      
        }
        // skip over padding, if any
        fseek(inptr, padding_input, SEEK_CUR);        
    }
    // change witdth, height and size off image
    bi.biWidth=bi.biWidth*scale;
    bi.biHeight=bi.biHeight*scale;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi.biHeight); 
   
    // return to start of outfile
    fseek(outptr, 0, SEEK_SET); 

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
