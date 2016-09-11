#define _XOPEN_SOURCE
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char* argv[]) { 
    if (argc<2||argc>4) {
        printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
        return 1;
    }
    
    const char* DEFAULT_CHARSET="ASC2AlfabetPrintableSimbol.txt";
    FILE* charsetFile=NULL;
    int maxPasswordLength=4;
    char charSet[127];
    int maxNumberOfCharset=0;
    char salt[3];
    char* curentHashedPassword;
    char* hashedPassword = argv[1];
       
    if (argc>2){
        if(!(charsetFile=fopen(argv[2], "rb"))){
            maxPasswordLength= atoi(argv[2]);
            if (!maxPasswordLength){
                printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
                return 1;
            }
            if (argc==4){
                if(!(charsetFile=fopen(argv[2], "rb"))) 
                printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
                return 1;
            }  
        }
    }
  
    if(!charsetFile){
        if(!(charsetFile=fopen(DEFAULT_CHARSET, "rb"))){ 
        printf("no CharsetFile\n");
        return 1;
        }
    }
    
    char simbol;
    while(fread(&simbol, 1, 1, charsetFile)) { 
        if (simbol!=0x0a && maxNumberOfCharset<127) {
            charSet[maxNumberOfCharset]=simbol; 
            maxNumberOfCharset++;
        } 
    }
     
    fclose(charsetFile);
    charSet[maxNumberOfCharset]=0;
    maxNumberOfCharset--;
        
    char curentPassword[maxPasswordLength+1];
    int nextNumberIncharset[maxPasswordLength+1];
    
    for(int i=0; i<=maxPasswordLength; i++){
        curentPassword[i]=0;
        nextNumberIncharset[i]=0;
    }  
    curentPassword[0]=charSet[0];
    
    for(int i=0; i<2; i++) salt[i]=hashedPassword[i];
    salt[2]=0;
       
    int i; 
    do{
        curentHashedPassword=crypt(curentPassword, salt);
        //printf("%s %s\n", curentPassword, curentHashedPassword);
        if (!(strcmp(hashedPassword, curentHashedPassword))){
            printf("%s\n", curentPassword);
            return 0;
        }
    
        i=0;
        for(;i<maxPasswordLength;i++){
            if(nextNumberIncharset[i]>maxNumberOfCharset){
                curentPassword[i]=charSet[0];
                nextNumberIncharset[i]=1;
            }else{ 
                curentPassword[i]=charSet[nextNumberIncharset[i]];
                nextNumberIncharset[i]++;
                break;
            }
        }   
    }while(i<maxPasswordLength);
    
printf("no craked\n");
return 0;
}
