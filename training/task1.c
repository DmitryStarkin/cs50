#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {

   char* line;
   int curentNumber;
    
   line = (char*) malloc(sizeof(char)*30001);
   fgets(line, 30001, stdin);
   if (line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
   } 
       int prewNumber[2] = {0,1};
       int len = strlen(line); 
       curentNumber = 1;
       while(true) {
            if (curentNumber > len) {
                break;
            } else {
                printf("%c", line[curentNumber-1]);   
            }
            curentNumber=prewNumber[0] + prewNumber[1];
            prewNumber[0] = prewNumber[1];
            prewNumber[1] = curentNumber;          
        }
    
    printf("\n");
    free(line);
}
