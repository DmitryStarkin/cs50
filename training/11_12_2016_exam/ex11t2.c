#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void){
    char str[1002];
    int yes = 1;
    fgets(str, 1000, stdin);
    if (str[strlen(str)-1] = '\n'){
        str[strlen(str)-1] = '\0';
    }
    char *tmp = str;
    int counter = 0;
    int prevFlag = 0;

    for(;*tmp;tmp++){

        if (counter == 0 && (islower(*tmp) || isdigit(*tmp))){
            if (prevFlag){
                prevFlag = 0;
                counter++;
                continue;
            }
            yes = 0;
            break;
        }
        if ( counter == 1 && (isupper(*tmp) || isdigit(*tmp))){
            if (isupper(*tmp)){
                prevFlag = 1;
            }
            counter = 0;
            continue;
        }
        if ( counter == 1 && (!islower(*tmp))){
            yes = 0;
            break;
        }
        if ( counter == 2 && !isdigit(*tmp)){
            yes = 0;
            break;
        }
        if(counter == 2){
            prevFlag = 1;
            counter = 0;
        } else {
            counter++;
        }
    }

    if (yes){
        printf("YES");
    } else {
        printf("NO");
    }

}