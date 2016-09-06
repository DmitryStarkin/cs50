#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{ 
    const int VALUESofCOINS[]={25,10,5,1}; 
    int curentValue=0;
    int coins=0;
    float summa=0;
    
    while(summa<1) { 
        printf("hai! How much change is owed?\n");
        summa = GetFloat();
        summa = summa*100;
    }
    
    int amountInCents = (int) round(summa);
    
    while(amountInCents){
    
        while(amountInCents>=VALUESofCOINS[curentValue])
            {
                amountInCents -= VALUESofCOINS[curentValue];
                coins++; 
            }
        curentValue++;
    }
   
    printf("%d\n", coins); 
    return 0;
}
