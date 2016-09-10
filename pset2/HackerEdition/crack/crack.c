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
    
    FILE* charsetFile;
    int maxPasswordLength;
    char* defaultCharsetFile="ASC2AlfabetPrintableSimbol.txt";
    char* charSet;
    char* hashedPassword = argv[1];
    char* curentHashedPassword;
    char salt[3];
    char curentPassword[5];
    curentPassword[4]=0;
    
    if (argc>2){
        if(!(charsetFile=fopen(argv[2], "rb"))){
            maxPasswordLength= atoi(argv[2]);
            if (!maxPasswordLength){
                printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
                return 1;
            }
            if (argc==4){
                if(!(charsetFile=fopen(argv[2], "rb"))) printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
            }else if(!(charsetFile=fopen(defaultCharsetFile, "rb"))) printf("no CharsetFile\n");  
        }else maxPasswordLength=4;
    }
        
    
    for(int i=0; i<2; i++) salt[i]=hashedPassword[i];
    salt[2]=0;
    
    printf("%s\n", salt);
    for (int i=0; i<123; i++){
    if(i==1) i=65;
    if(i==91) i=97;
    curentPassword[3]=i;
    for (int y=0; y<123; y++){
    if(y==1) y=65;
    if(y==91) y=97;
    curentPassword[2]=y;
    for (int k=0; k<123; k++){
    if(k==1) k=65;
    if(k==91) k=97;
    curentPassword[1]=k;
    for (int j=65; j<123; j++){
    if(j==91) j=97;
    curentPassword[0]=j;
    curentHashedPassword=crypt(curentPassword, salt);
    printf("%s %s\n", curentPassword, curentHashedPassword);
   if (!(strcmp(hashedPassword, curentHashedPassword))){
   printf("%s\n", curentPassword);
   return 0;
   }
    
    }
    }
    }
    }
   
   
    
   printf("no craked\n");
return 0;
}
