/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    BYTE buffer[512];
    int curentFileNumber = 0;
    char curentFileName[8]; 
         
    // ensure proper usage
    if (argc != 2){
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // open input file 
    FILE* inputFile = fopen(argv[1], "rb");
    if (inputFile == NULL){
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }
    
    // greate pointer output file   
    FILE* outFile = NULL;
    
    // read input file 
    while (true) {
        fread(buffer, 512, 1, inputFile);
        if (feof(inputFile)) break;
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff)) {
            
            //if there is
            if (outFile) {
                // cloze output file
                fclose(outFile);
            }
            
            //named out file
            sprintf(curentFileName, "%03d.jpg", curentFileNumber++);
            outFile = fopen(curentFileName, "wb");
            if (outFile == NULL){
                fclose(inputFile);
                fprintf(stderr, "Could not create %s.\n", curentFileName);
                return 3;
            }  
        }
        //this check skips the beginning of the input file
        if (outFile) {
        
            // write out file
            fwrite(buffer, 512, 1, outFile); 
        }    
    }
 
    // close infile
    fclose(inputFile);

    // close outfile
    fclose(outFile);

    // that's all folks
    return 0;    
}
    
    
    

