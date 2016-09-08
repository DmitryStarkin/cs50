#include <cs50.h>
#include <stdio.h>

int main(void){

int height=-1;

    while(height<0 || height>23) {
        printf("hello, write integer up to 23\n");
        height = GetInt();
    }
    for(int line=0; line<height; line++) {
        for(int space=1; space<height-line; space++){
            printf(" ");
        }
        for(int sharp=0; sharp<(height-(height-line)+1); sharp++){
            printf("#");
        }
        printf("#\n");
    }
    return 0;
}
