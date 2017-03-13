#include <cs50.h>
#include <stdio.h>
#include <math.h>


/*
return the number of digits in the number
*/
int NumberLength(long long int number);

/*
return 1 if length is not in the array VALID_LENGTH
otherwise returns 0
*/
int LenthInvalid(int length, const int* VALID_LENGTH);

/*
return 1 f the first digit number is in the array FIRST_DIGITS
otherwise returns 0
!!!! note
the size Digits should be larger than the number of digits of the greatest number in FIRST_DIGITS
*/
int IsFirstDigits(const int* FIRST_DIGITS, int* Digits);

int main(void) {
    const int VALID_LENGTH[] = {13, 15, 16, 0}; /*set of right card number length, must end with zero*/
    const int AMEX_FIRST_DIGITS[] = {34, 37, 0}; /*set valid first digits of AMEX, must end with zero*/
    const int MASTERCARD_FIRST_DIGITS[] = {51, 52, 53, 54, 55, 0}; /*set valid first digits of MASTERCARD, must end with zero*/
    const int VISA_FIRST_DIGITS[] = {4, 0}; /*set valid first digits of VISA, must end with zero*/
    long long int cardNumber;
    int cardNumberlength;
    int controlSum = 0;
    do {
        printf("CardNumber:");
        cardNumber = GetLongLong();
    } while(cardNumber < 0);
    cardNumberlength = NumberLength(cardNumber);
    if(LenthInvalid(cardNumberlength, VALID_LENGTH)) {
        printf("INVALID length\n");
        return 0;
    }
    int Digits[cardNumberlength];
    for(int i = cardNumberlength - 1; cardNumber; i--) {
        Digits[i] = cardNumber % 10;
        cardNumber /= 10;
    }
    for(int i = 1; i <= cardNumberlength; i++) {
        if(i % 2)controlSum += Digits[cardNumberlength - i];
        else if(Digits[cardNumberlength - i] * 2 > 9) controlSum += Digits[cardNumberlength - i] * 2 - 9;
        else controlSum += Digits[cardNumberlength - i] * 2;
    }
    if(controlSum % 10) {
        printf("INVALID control sum\n");
        return 0;
    }
    if(IsFirstDigits(AMEX_FIRST_DIGITS, Digits)) {
        printf("AMEX\n");
        return 0;
    }
    if(IsFirstDigits(MASTERCARD_FIRST_DIGITS, Digits)) {
        printf("MASTERCARD\n");
        return 0;
    }
    if(IsFirstDigits(VISA_FIRST_DIGITS, Digits)) {
        printf("VISA\n");
        return 0;
    }
    printf("INVALID, card is not supported\n");
    return 0;
}

int NumberLength(long long int number) {
    int length = 0;
    if(!number) return 1;
    while(number) {
        number /= 10;
        length++;
    }
    return length;
}

int LenthInvalid(int length, const int* VALID_LENGTH) {
    for(int i = 0; length - VALID_LENGTH[i]; i++) {
        if(!VALID_LENGTH[i]) return 1;
    }
    return 0;
}

int IsFirstDigits(const int* FIRST_DIGITS, int* Digits) {
    int length;
    int digitsForvalidate = 0;
    while(*FIRST_DIGITS) {
        length = NumberLength(*FIRST_DIGITS);
        for(int i = 0; i < length; i++) {
            digitsForvalidate = digitsForvalidate * 10 * i + Digits[i];
        }
        if(*FIRST_DIGITS - digitsForvalidate) FIRST_DIGITS++;
        else return 1;
    }
    return 0;
}

