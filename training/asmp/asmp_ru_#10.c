#include <stdio.h>
#include <stdlib.h>

int main(){
    
    FILE* inFile;
    char inputNumber[29];
    int koef[4];


    inFile = fopen("input10.txt", "r");

    fgets (inputNumber, 29, inFile);

    char *tmp, *tmp2;
    tmp = tmp2 = inputNumber;
    int numbercount = 0;

    for (;*tmp;tmp++){
        if (*tmp == ' ' || *tmp == '\n'){
            *tmp='\0';
            koef[numbercount] = atoi(tmp2);
            numbercount++;
            tmp2 = tmp + 1;
        }
    }
    
    for (int i = -100; i <= 100; i++){
    
        if (!(koef[0]*i*i*i + koef[1]*i*i +  koef[2]*i +  koef[3])){
        printf ("%d ", i); 
        }
    }
    printf ("\n");
}
