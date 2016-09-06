#include <cs50.h>
#include <stdio.h>
#include <math.h>

int NumberLength(long long int number);
int LenthInvalid(int length, const int* VALID_LENGTH);

int main(void)
{ 
    const int VALID_LENGTH[]={13, 15, 16, 0};/*must end with zero*/
    long long int cardNumber;
    int length;
    int controlSum=0;
    
    do{ 
        printf("CardNumber:");
        cardNumber = GetLongLong();
    } while(cardNumber<0);
    
    length=NumberLength(cardNumber);
    
    if(LenthInvalid(length, VALID_LENGTH)){
       printf("INVALID\n");
       return 0;
    }
    
    int Digits[length];
    
    for(int i=length-1; cardNumber; i--){
        Digits[i]=cardNumber%10;
    cardNumber/=10;
    }
    
    for (int i=0; i<length; i++){
        printf("%d\n", Digits[i]);
    }
    
    for (int i=0; i<length; i++){
        if (i%2) {
            if (Digits[i]*2>10) controlSum+=Digits[i]*2-9;
            else controlSum+=Digits[i]*2;
        }else controlSum+=Digits[i];
    }
   
    printf("%d\n", controlSum);
   
    if (controlSum%10) {
        printf("INVALID\n");
        return 0;
    }
     
return 0;
}

int NumberLength(long long int number){
int length=0;
    if(!number) return 1;
    while(number){
        number/=10;
        length++;
    }
return length;

}

int LenthInvalid(int length, const int* VALID_LENGTH){
    for (int i=0; length-VALID_LENGTH[i];i++){
        if(!VALID_LENGTH[i]) return 1;
    }
return 0;

}
