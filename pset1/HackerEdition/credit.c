#include <cs50.h>
#include <stdio.h>
#include <math.h>


/*return the number of digits in the number
*/
int NumberLength(long long int number);

/*return 1 if length is not in the array VALID_LENGTH
otherwise returns 0
*/
int LenthInvalid(int length, const int* VALID_LENGTH);

/*return 1 if the first digits of the number match a valid number
otherwise returns 0
*/
int IsFirstDigits(const int* FIRST_DIGITS, long long int number);

/*return a checksum off number computed by the algorithm Hans Peter Luhn
*/
int LuhnControlSum(long long int number);

int main(void)
{ 
    const int VALID_LENGTH[]={13, 15, 16, 0};/*set of right card number length, must end with zero*/
    const int AMEX_FIRST_DIGITS[]={34, 37, 0};/*set valid first digits of AMEX, must end with zero*/
    const int MASTERCARD_FIRST_DIGITS[]={51, 52, 53, 54, 55, 0};/*set valid first digits of MASTERCARD, must end with zero*/
    const int VISA_FIRST_DIGITS[]={4,0};/*set valid first digits of VISA, must end with zero*/
    
    long long int cardNumber;
       
    do{ 
        printf("CardNumber:");
        cardNumber = GetLongLong();
    } while(cardNumber<0);
     
    if(LenthInvalid(NumberLength(cardNumber), VALID_LENGTH)){
       printf("INVALID length\n");
       return 0;
    }
        
    if (LuhnControlSum(cardNumber)%10){
        printf("INVALID control sum\n");
        return 0;
    }
      
    if (IsFirstDigits(AMEX_FIRST_DIGITS, cardNumber)){
        printf("AMEX\n");
        return 0;
    } 
    
    if (IsFirstDigits(MASTERCARD_FIRST_DIGITS, cardNumber)){
        printf("MASTERCARD\n");
        return 0;
    } 
    
    if (IsFirstDigits(VISA_FIRST_DIGITS, cardNumber)){
        printf("VISA\n");
        return 0;
    } 
    
       
    printf("INVALID, card is not supported\n");    
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

int IsFirstDigits(const int* FIRST_DIGITS, long long int number){
int firstDigitslength;
int numberLength;
long long int remove;

    numberLength=NumberLength(number);
    while (*FIRST_DIGITS){
        remove=1;
        firstDigitslength=NumberLength(*FIRST_DIGITS);
        for (int i=0, y=numberLength-firstDigitslength; i<y; i++){
        remove*=10; 
        }
        if (*FIRST_DIGITS-(number/remove))FIRST_DIGITS++;
        else return 1;
    }
    
return 0;
}

int LuhnControlSum(long long int number){
int controlSum=0;
int curentDighit=0;
int dighitCounter=1;

    while(number){
        curentDighit=number%10;
        if (dighitCounter%2)controlSum+=curentDighit;
            else if (curentDighit*2>9) controlSum+=curentDighit*2-9;
                    else controlSum+=curentDighit*2; 
        number/=10;
        dighitCounter++;  
    }
    
return controlSum;
}





