#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct longNum {
    char *digitsBeforePoint;
    char *digitsAfterPoint;
    unsigned char isNegative;
};

#typedef struct longNum longNumber;

const int MEM_MULT = 2;
const int INITIAL_BIT = 15;

char* readString(FILE* inFile);
void inverseString(char* string);
longNumber* stringToLongNumber(char* string);
char* longNumberToString(longNumber* longNum);
void killLongNumber(longNumber* longNum);
int addTwoLongNum(char* Result, char* firstNum, char* secondNum);
longNumber* summLongNums(longNumber* firstNum, longNumber* secondNum);
int summNumberDigit(char *digits);
void removBeginZero(char *digits);
char* removBeginZeroMP(char* digits);

int main(void){
    
    FILE* inFile;
    char* result = malloc(sizeof(char));
    inFile = fopen("input2.txt" ,"rb");
    if (!inFile)
    {
        return 0;
    }
    char* firstNum = readString(inFile);
    char* secondNum = readString(inFile);
    
    fclose (inFile);
    
    printf("%s \n", firstNum);
    printf("%s \n", secondNum);
    inverseString(firstNum);
    inverseString(secondNum);
    addTwoLongNum(result, firstNum, secondNum);
    inverseString(result);
    printf("%s \n", result);
    
    free(firstNum);
    free(secondNum);
    free(result);
}

char* readString(FILE* inFile){

    
    int symbolCount = 0;
    int memSize = INITIAL_BIT;
    unsigned char symbol;
    char* retMem = NULL;
    char* string = NULL;
    
    if (!(string = malloc(memSize * sizeof(char)))){
       return  string; 
    }
    
    while(1){
        fread(&symbol, 1, 1, inFile);
        if (ferror(inFile)){
            if (string){
                free(string);
                string = NULL;
            }
        break;
        }
        
        if(symbolCount == memSize){
        memSize *= MEM_MULT;
            if(retMem = realloc(string, memSize * sizeof(char))){
                string = retMem;
            } else {
                if (string) {
                    free(string);
                    string = NULL;
                }
            break;   
            }
        }
      
        if (symbol == 0x0a || symbol == 0x0d || feof(inFile)){
            *(string + symbolCount) = '\0';
            break;
        } else {
            *(string + symbolCount) = symbol;   
            symbolCount++;
        }
    }
    
    if(string && (retMem = realloc(string, (symbolCount + 1) * sizeof(char)))){
        string = retMem;
    }
    
    return  string;
}

void inverseString(char* string){
    if (!strlen(string)){
        return;
    }
    char tmp;
    for (int i = 0, y = strlen(string)-1, k = (y+1)/2; i < k; i++, y--){
       tmp = string[i];
       string[i] = string[y];
       string[y] = tmp;
    }
}

longNumber* stringToLongNumber(char* string){
    
    if (!string || !strlen(string)){
        return NULL;
    }
    
    char* tmpString = string; 
    longNumber* number;
    
    if (!(number = malloc(sizeof(longNumber)))){
       return  number; 
    }
    
    int memSize = INITIAL_BIT;
    
    number->digitsBeforePoint;
    if (!(number->digitsBeforePoint = malloc(memSize * sizeof(char)){
       free(number); 
       return  number; 
    }
    
    number->digitsAfterPoint = NULL;
    int symbolCount = 0;
    char* retMem = NULL;
    
    if (*tmpString == '-'){
        number->isNegative = 1;
        tmpString++;
    } else {
        number->isNegative = 0;    
    }
    
    char **tmpDigits = number->digitsBeforePoint;
    
    while(1){
        
        if(symbolCount == memSize){
            memSize *= MEM_MULT;
            if(retMem = realloc(*tmpDigits, memSize * sizeof(char))){
                *tmpDigits = retMem;
            } else {
                killLongNumber(number);
                break;   
            }
        }
      
        if (*tmpString == '\0' || *tmpString == '.'){
            *(*tmpDigits + symbolCount) = '\0';
            if(retMem = realloc(*tmpDigits, (symbolCount + 1) * sizeof(char))){
                *tmpDigits = retMem;
            }
            //inverseString(*tmpDigits);
            if(*tmpString == '.'){
                if(number->digitsAfterPoint){
                    killLongNumber(number);
                    break;     
                }
                memSize = INITIAL_BIT;
                if (!(number->digitsAfterPoint = malloc(memSize * sizeof(char)){
                    killLongNumber(number);
                    break;    
                }
                **tmpDigits = number->digitsAfterPoint;
                symbolCount = 0;
            } else {
                break;
            }
        } else {
            if(*tmpString > '9' || *tmpString < '0'){
                killLongNumber(number);
                break;       
            }
            *(*tmpDigits + symbolCount) = *tmpString;   
            symbolCount++;
        }
       tmpString++; 
    }
    
    if (number){
        if(!strlen(number->digitsBeforePoint) && !strlen(number->digitsAfterPoint)){
            killLongNumber(number);  
        } else if(!summNumberDigit(number->digitsBeforePoint) && !summNumberDigit(number->digitsAfterPoint)){
           number->isNegative = 0;
           
        }
    }
    return number; 
}

void killLongNumber(longNumber* longNum){
    if (longNum){
        if(longNum->digitsBeforePoint){
            free(longNum->digitsBeforePoint);
        }
        if(longNum->digitsAfterPoint){
            free(longNum->digitsAfterPoint);  
        }
        free(longNum);
        longNum = NULL;
    } 
}

int summNumberDigit(char *digits){
    
    char *tmp = digits;
    int summa = 0;
    
    for (;*tmp; tmp++){
       summa += (int)(*tmp - 48); 
    }
    return summa;
}

void removBeginZero(char *digits){
    
    char* tmp = removBeginZeroMP(digits);

    if(tmp - digits){
        for(int diff = tmp - digits; *(tmp - 1); tmp++){
            *(tmp - diff) = *tmp;
        }
    } 
}

char* removBeginZeroMP(char* digits){
   
    for(;*digits == '0'; digits++);
    
    return digits;
}

int addTwoLongNum(char* result, char* firstNum, char* secondNum){
    
    int resultDigits = 0;
    int addDigit = 0;
    int firstNumDigit, secondNumDigit;
    char *firstTmp, *secondTmp;
    firstTmp = firstNum;
    secondTmp = secondNum;
    
    while (*firstTmp || *secondTmp){
        result = realloc(result, (resultDigits + 1) * sizeof(char));
        *secondTmp ? (secondNumDigit = *secondTmp - 48) : (secondNumDigit = 0);
        *firstTmp ? (firstNumDigit = *firstTmp- 48) : (firstNumDigit = 0);
        *(result + resultDigits) = ((firstNumDigit + secondNumDigit + addDigit)%10) + 48; 
        addDigit = (firstNumDigit + secondNumDigit + addDigit)/10;
        resultDigits++;
        if (*firstTmp){
           firstTmp++; 
        }
        if (*secondTmp){
           secondTmp++; 
        }
    }
    if (addDigit){
    result = realloc(result, (resultDigits + 1) * sizeof(char));
    *(result + resultDigits) = addDigit + 48;
    resultDigits++;
    }
    result = realloc(result, (resultDigits + 1) * sizeof(char));
    *(result + resultDigits) = '\0';
    return resultDigits;
}