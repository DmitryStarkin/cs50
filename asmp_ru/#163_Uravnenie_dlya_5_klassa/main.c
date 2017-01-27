#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char formula[6];
    fgets(formula, 6, stdin);
    int flag = 1;

    for(int i = 0; i < 5; i++){
        if(formula[i] == 'x'){
            if( i == 4){
              formula[i] = 1;
            } else {
               formula[i] = (formula[4] - 48) * -1;
               flag = 0;
               if (i == 2 && formula[1] == '-'){
                   formula[4] = 1;
                   formula[1] = '+';
                } else {
                   formula[4] = -1;
                }
           }

        } else {
            if (isdigit(formula[i]) && (flag || (i != 4))){
            formula[i] = formula[i] - 48;
            }
            }
    }

    int result;
    if (formula[1] == '-') {
        result = (formula[0] - formula[2]) * formula[4];
    } else {
        result = (formula[0] + formula[2]) * formula[4];
    }

    printf ("%i\n", result);
}
