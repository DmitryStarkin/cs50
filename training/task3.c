#include <stdio.h>
#include <stdlib.h>
    
int main(void){
    
    int size = 1;
    printf("enter array length\n");
    scanf("%d", &size);
    scanf("%*c"); 
    char line[size * 5 + 1];
    char curentNumber[5];
    int numbers[size];
    int sum = 0;
    int mult = 1;
    printf("enter array string \n");
    if (!fgets(line, size * 5 + 1, stdin)) {
        printf("read error\n");
    }
    int count = 0, numCount = 0;
    char *tmp = line;
    for(;*tmp; tmp++){
        if(*tmp == ' '|| *tmp == '\n'){
            curentNumber[count] = '\n';
            count=0;
            numbers[numCount++] = atoi( curentNumber); 
        } else {
            curentNumber[count++] = *tmp;
        }
    }
    int mini, maxi;
        mini = maxi = 0;
    for (int i = 0; i < size; i++){
        if(numbers[i] > 0){
            sum += numbers[i];
        }
        if(numbers[i]>numbers[maxi]){
            maxi = i;
        }
        if(numbers[i]<numbers[mini]){
            mini = i;
        }
    }
    if (mini > maxi){
        int tmp = mini;
        mini = maxi;
        maxi = tmp;
    }
    for(int i = mini+1; i<maxi; i++){
        mult *= numbers[i];
    }
    if ((maxi - mini) == 1) {
        mult = 0;    
    }
    printf("%i %i", sum, mult);    
}
