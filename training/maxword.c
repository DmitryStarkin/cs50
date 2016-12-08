#include <stdio.h>
#include <string.h>

int main (void){

    char line[100];
    int curentWordLength, maxWordLength;
    char *maxWord, *tmp;
    curentWordLength = maxWordLength = 0;

    printf ("enter string: ");
    fgets(line, 100, stdin);
    printf ("\nmax Word: ");
    if (line[strlen(line)-1]=='\n'){
        line[strlen(line)-1]='\0';
    }
    tmp=line;
    
    for (; *tmp; tmp++){
        if (*tmp == ' ') {
            *tmp='\0';
            if (curentWordLength > maxWordLength){
                maxWordLength = curentWordLength;
                maxWord = tmp - maxWordLength;
            }
            curentWordLength = 0;
        }else{
            curentWordLength++;
        }
    }
    if (curentWordLength > maxWordLength){
                maxWord = tmp - curentWordLength;
            }
    printf("%s\n", maxWord);
}
