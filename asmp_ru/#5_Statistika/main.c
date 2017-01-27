#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    char arrayLen[4];
    int counter = 0;
 
    FILE *inptr = fopen("input.txt", "r");

    fgets(arrayLen, 4, inptr);

    if (arrayLen[strlen(arrayLen)-1] == '\n'){
        arrayLen[strlen(arrayLen)-1] = '\0';  
    }

    char numberArray[atoi(arrayLen) * 2 + atoi(arrayLen) + 1];

    fgets(numberArray, (atoi(arrayLen) * 2 + atoi(arrayLen) + 1), inptr);

    fclose(inptr);

    numberArray[strlen(numberArray)-1] = ' ';  

    char*tmp, *num, *num1;

    tmp =  num = num1 = numberArray;

    for (; *tmp; tmp++){
        if (*tmp == ' '){
            *tmp = '\0';
            if (atoi(num)%2){
                printf ("%s ", num);
                counter++;
                num = tmp + 1;
             } else {
                    for (;*num; num1++, num++){
                        *num1 = *num;
                    }
               *num1 =' ';
               num1++;
               num++;
            }
        }
    }
    
    printf ("\n");
    printf ("%s\n", numberArray);
    
    if ((atoi(arrayLen)/2) < counter){
       printf ("NO\n"); 
    }else{
       printf ("YES\n"); 
    }
} 
