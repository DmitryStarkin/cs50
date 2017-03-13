/**
 * resize2.c
 *
 *
 *
 * resizes a BMP  float factor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

struct imgContayner {
    BITMAPFILEHEADER imgFileHeader;
    BITMAPINFOHEADER imgInfoHeader;
    RGBTRIPLE **pixelsArray;
};

typedef struct imgContayner bmpImage;

/**
read image from file to memory (need clearImage after usage)
*/
int readImageFromFile(FILE *imgInputFile, bmpImage *image);

/**
write image from memory to file
*/
int writeImageToFile(FILE *imgOutputFile, bmpImage *image);

/**
unload image (free memory)
*/
void clearImage(bmpImage *image);

/**
resize image (greate new image in memory, need clearImage after usage)
*/
int resizeImage(bmpImage *inputImage, bmpImage *outputImage, float scale);

int main(int argc, char* argv[]) {
    // ensure proper usage
    if(argc != 4) {
        printf("Usage: ./resize scale(integer < 100.0) infile outfile\n");
        return 1;
    }
    // remember filenames and scale
    float scale;
    char trach;
    char* infile = argv[2];
    char* outfile = argv[3];
    if(sscanf(argv[1], " %f %c", &scale, &trach) != 1) {
        fprintf(stderr, "Usage: ./resize scale(float < 100.0) infile outfile\n");
        return 1;
    }
    if(scale <= 0 | scale > 100) {
        fprintf(stderr, "Usage: ./resize scale(float < 100.0) infile outfile\n");
        return 1;
    }
    // open input file
    FILE* inptr = fopen(infile, "r");
    if(inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // define contayners for images
    bmpImage inputImage;
    bmpImage outputImage;
    inputImage.pixelsArray = NULL;
    outputImage.pixelsArray = NULL;
    // load input image
    int result = readImageFromFile(inptr, &inputImage);
    if(result) {
        fclose(inptr);
        return result;
    }
    // close input file
    fclose(inptr);
    if(resizeImage(&inputImage, &outputImage, scale)) {
        //unload images from memory
        clearImage(&inputImage);
        clearImage(&outputImage);
        fprintf(stderr, "Resize Error\n");
        return 5;
    }
    //unload input image from memory
    clearImage(&inputImage);
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if(outptr == NULL) {
        clearImage(&outputImage);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    // write output image
    result = writeImageToFile(outptr, &outputImage);
    if(result) {
        // close output file
        fclose(outptr);
        //unload output image from memory
        clearImage(&outputImage);
        return result;
    }
    // close output file
    fclose(outptr);
    //unload output image from memory
    clearImage(&outputImage);
    // that's all folks
    return 0;
}

int readImageFromFile(FILE *imgInputFile, bmpImage *image) {
    // read infile's BITMAPFILEHEADER
    fread(&(image->imgFileHeader), sizeof(BITMAPFILEHEADER), 1, imgInputFile);
    // read infile's BITMAPINFOHEADER
    fread(&(image->imgInfoHeader), sizeof(BITMAPINFOHEADER), 1, imgInputFile);
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if(image->imgFileHeader.bfType != 0x4d42 || image->imgFileHeader.bfOffBits != 54 || image->imgInfoHeader.biSize != 40 ||
            image->imgInfoHeader.biBitCount != 24 || image->imgInfoHeader.biCompression != 0) {
        return 4;
    }
    // determine heigt and width
    int imgHeight = image->imgInfoHeader.biHeight;
    int imgWidth = image->imgInfoHeader.biWidth;
    // determine padding for scanlines
    int padding = (4 - (imgWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //assigned memory for image
    image->pixelsArray = calloc(abs(imgHeight), sizeof(RGBTRIPLE*));
    for(int i = 0; i < abs(imgHeight); i++) {
        *(image->pixelsArray + i) =  calloc(imgWidth, sizeof(RGBTRIPLE));
    }
    //load image
    // iterate over infile's scanlines
    for(int i = 0, height = abs(imgHeight); i < height; i++) {
        // iterate over pixels in scanline
        for(int j = 0; j < imgWidth; j++) {
            // read RGB triple from infile
            fread((*(image->pixelsArray + i) + j), sizeof(RGBTRIPLE), 1, imgInputFile);
        }
        // skip over padding, if any
        fseek(imgInputFile, padding, SEEK_CUR);
    }
    return 0;
}

int writeImageToFile(FILE *imgOutputFile, bmpImage *image) {
    // write outfile's BITMAPFILEHEADER
    fwrite(&(image->imgFileHeader), sizeof(BITMAPFILEHEADER), 1, imgOutputFile);
    // write outfile's BITMAPINFOHEADER
    fwrite(&(image->imgInfoHeader), sizeof(BITMAPINFOHEADER), 1, imgOutputFile);
    // determine heigt and width
    int imgHeight = image->imgInfoHeader.biHeight;
    int imgWidth = image->imgInfoHeader.biWidth;
    // determine padding for scanlines
    int padding = (4 - (imgWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //write image
    // iterate over outfile's scanlines
    for(int i = 0, height = abs(imgHeight); i < height; i++) {
        // iterate over pixels in scanline
        for(int j = 0; j < imgWidth; j++) {
            // read RGB triple from infile
            //TODO the error handler
            // write RGB triple to outfile
            fwrite((*(image->pixelsArray + i) + j), sizeof(RGBTRIPLE), 1, imgOutputFile);
        }
        // add padding back (to demonstrate how)
        for(int k = 0; k < padding; k++) {
            fputc(0x00, imgOutputFile);
        }
    }
    return 0;
}

void clearImage(bmpImage *image) {
    //TODO what structure is initialized when creating?
    //if (*image){
    // determine heigt
    int imgHeight = image->imgInfoHeader.biHeight;
    if(image->pixelsArray) {
        for(int i = 0; i < abs(imgHeight); i++) {
            if(*(image->pixelsArray + i)) {
                free(*(image->pixelsArray + i));
            }
        }
        free(image->pixelsArray);
    }
    //}
}

int resizeImage(bmpImage *inputImage, bmpImage *outputImage, float scale) {
    int inImgHeight = inputImage->imgInfoHeader.biHeight;
    int inImgWidth = inputImage->imgInfoHeader.biWidth;
    //initialise out image headers
    outputImage->imgFileHeader = inputImage->imgFileHeader;
    outputImage->imgInfoHeader = inputImage->imgInfoHeader;
    //calculate and write out file and out image size, heigt and width
    int outImgHeight = outputImage->imgInfoHeader.biHeight = (int) ceil(inImgHeight * scale);
    int outImgWidth = outputImage->imgInfoHeader.biWidth = (int) ceil(inImgWidth * scale);
    // determine padding for scanlines
    int outPadding = (4 - (outImgWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outputImage->imgInfoHeader.biSizeImage = (outImgWidth * sizeof(RGBTRIPLE) + outPadding) * abs(outImgHeight);
    outputImage->imgFileHeader.bfSize = ((outImgWidth * sizeof(RGBTRIPLE) + outPadding * sizeof(char)) * abs(outImgHeight)) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    //assigned memory for output image
    outputImage->pixelsArray = calloc(abs(outImgHeight), sizeof(RGBTRIPLE*));
    for(int i = 0; i < abs(outImgHeight); i++) {
        *((outputImage->pixelsArray) + i) =  calloc(outImgWidth, sizeof(RGBTRIPLE));
    }
    //resize algoritm http://ru.wikibooks.oxx.su
    int h, w;
    float t;
    float u;
    float tmp;
    // factors
    float factor1, factor2, factor3, factor4;
    //surrounding pixels
    RGBTRIPLE pic1, pic2, pic3, pic4;
    //color components
    BYTE red, green, blue;
    for(int i = 0; i < abs(outImgHeight); i++) {
        tmp = (float)(i) / (float)(abs(outImgHeight) - 1) * (abs(inImgHeight) - 1);
        h = (int) floor(tmp);
        if(h < 0) {
            h = 0;
        } else {
            if(h >= abs(inImgHeight) - 1) {
                h = abs(inImgHeight) - 2;
            }
        }
        u = tmp - h;
        for(int j = 0; j < outImgWidth; j++) {
            tmp = (float)(j) / (float)(outImgWidth - 1) * (inImgWidth - 1);
            w = (int) floor(tmp);
            if(w < 0) {
                w = 0;
            } else {
                if(w >= inImgWidth - 1) {
                    w = inImgWidth - 2;
                }
            }
            t = tmp - w;
            factor1 = (1 - t) * (1 - u);
            factor2 = t * (1 - u);
            factor3 = t * u;
            factor4 = (1 - t) * u;
            pic1 = inputImage->pixelsArray[h][w];
            pic2 = inputImage->pixelsArray[h][w + 1];
            pic3 = inputImage->pixelsArray[h + 1][w + 1];
            pic4 = inputImage->pixelsArray[h + 1][w];
            blue = (BYTE) pic1.rgbtBlue * factor1 + (BYTE) pic2.rgbtBlue * factor2 + (BYTE) pic3.rgbtBlue * factor3 + (BYTE) pic4.rgbtBlue * factor4;
            green = (BYTE) pic1.rgbtGreen * factor1 + (BYTE) pic2.rgbtGreen * factor2 + (BYTE) pic3.rgbtGreen * factor3 + (BYTE) pic4.rgbtGreen * factor4;
            red = (BYTE) pic1.rgbtRed * factor1 + (BYTE) pic2.rgbtRed * factor2 + (BYTE) pic3.rgbtRed * factor3 + (BYTE) pic4.rgbtRed * factor4;
            outputImage->pixelsArray[i][j].rgbtBlue = blue;
            outputImage->pixelsArray[i][j].rgbtGreen = green;
            outputImage->pixelsArray[i][j].rgbtRed = red;
        }
    }
    return 0;
}
