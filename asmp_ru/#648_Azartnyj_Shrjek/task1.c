#include <stdio.h>
#include <stdlib.h>

int main(void)
{
int nums;
scanf("%i", &nums);
scanf("%*c");
int numsi[nums];
int numcount = 0;
char currentnum[4];
char numString[nums*4+2];

fgets(numString, nums*4+2, stdin);

char *tmp = numString;
char *tmp2 = currentnum;
for(;*tmp; tmp++){
    if (*tmp == 32 || *tmp == 10 || *tmp == '\0'){
        *tmp2 = '\0';
        numsi[numcount++] = atoi(currentnum);
        tmp2 = currentnum;
    } else {
        *tmp2 = *tmp;
        tmp2++;
    }
}

   int flag = 1;
   while(flag){
        flag = 0;
        for (int i = 0, tmpr = 0, j = 1; i < nums - 1; i++, j++){
            if (numsi[i] > numsi[j]){
                tmpr = numsi[j];
                numsi[j] = numsi[i];
                numsi[i] = tmpr;
                flag = 1;
            }
        }
    }

int shrek = 0;
int kr = 0;
for (int i = 0; i < nums; i++){
    if (i < nums/2){
        kr += numsi[i];
    }else{
        shrek += numsi[i];
    }
}
printf("%i\n", shrek - kr);
}