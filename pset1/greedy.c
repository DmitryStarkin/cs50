#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{ 
    const int NOMINAL1=25;
    const int NOMINAL2=10;
    const int NOMINAL3=5;
    const int NOMINAL4=1;
    int issue=0;
    float summa=0;
    while(summa<1) { 
        printf("hai! How much change is owed?\n");
        summa = GetFloat();
        summa = summa*100;
    }
    int cent = (int) round(summa);
    while(cent>=NOMINAL1)
    {
        cent= cent-NOMINAL1;
        issue++; 
    }
    while(cent>=NOMINAL2)
    {
        cent= cent-NOMINAL2;
        issue++; }
    while(cent>=NOMINAL3)
    {
        cent= cent-NOMINAL3;
        issue++;}
    while(cent>=NOMINAL4)
    {
        cent= cent-NOMINAL4;
        issue++; 
    }
    printf("%d\n", issue); 
}
