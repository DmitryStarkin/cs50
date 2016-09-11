#define _XOPEN_SOURCE
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char* argv[]) { 
    //check the arguments
    if (argc<2||argc>4) {
        printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
        return 1;
    }
    
    const char* DEFAULT_CHARSET="ASC2AlfabetPrintableSimbol.txt";
    FILE* charsetFile=NULL;
    int maxPasswordLength=4;
    char charSet[128];
    char salt[3];
    register char* hashedPassword = argv[1];
    
    //read and check optional arguments if there are   
    if (argc>2){
        //if the third argument is not a file
        if(!(charsetFile=fopen(argv[2], "rb"))){
            //read it as a number
            maxPasswordLength= atoi(argv[2]);
            if (!maxPasswordLength){
                printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
                return 1;
            }
            //if the fourth is trying to open the file
            if (argc==4){
                if(!(charsetFile=fopen(argv[3], "rb"))){ 
                    printf("Usage: ./crack hashedPassword [maxPasswordLength] [passswordGharSetFileName]\n");
                    return 1;
                }
            }  
        }
    }
    
    //if no charsetFile open default
    if(!charsetFile){
        if(!(charsetFile=fopen(DEFAULT_CHARSET, "rb"))){ 
        printf("no CharsetFile or open error\n");
        return 1;
        }
    }
    
    //charset array initialization
    for(int i=0; i<128; i++){
        charSet[i]=0;
    }
    
    // read simbols from file and write in charset array
    char simbol; 
    for(int i=0;  fread(&simbol, 1, 1, charsetFile);){
        //not read more 127 simbols
        if (simbol!=0x0a && i<128) {
        charSet[i]=simbol;
        i++;
        }       
    }     
    fclose(charsetFile);
    
   
    //arrays for password to compare and number curent simbols from charset in password     
    char curentPassword[maxPasswordLength+1];
    int nextNumberIncharset[maxPasswordLength+1];
    
    //curentPassword and nextNumberIncharset initialization
    for(int i=0; i<=maxPasswordLength; i++){
        curentPassword[i]=0;
        nextNumberIncharset[i]=0;
    }
    
    //set first password to compare  
    curentPassword[0]=charSet[0];
    nextNumberIncharset[0]=1;
    
    //extract salt from hashedPassword
    for(int i=0; i<2; i++) salt[i]=hashedPassword[i];
    salt[2]=0;
    
    //register is interpreted as "access needs to speed up" depends on the compiler   
    register int positionOfSimbol;
    register char* curentHashedPassword;
    register char* tmp; 
    
    do{
        //as the pointer moves assign its value to a temporary variable
        tmp=hashedPassword;
        //encrypted current password
        curentHashedPassword=crypt(curentPassword, salt);
        //this blosk of code compare two string (curentHashedPassword and hashedPassword) 
        //for speed, we avoid call function strcmp
        while (*curentHashedPassword==*tmp) {
            if (!(*tmp)){
                //when the coincidence output current password
                printf("%s\n", curentPassword);
                return 0;
            }
            tmp++;
            curentHashedPassword++;
        }
        
        positionOfSimbol=0;
        //this block of code return current password as next combination of charset simbol not long of maxPasswordLength
        //it is considered that the address arithmetic is slightly faster than indexing
        for(;positionOfSimbol<maxPasswordLength;positionOfSimbol++){
            if(*(charSet+*(nextNumberIncharset+positionOfSimbol))){
                *(curentPassword+positionOfSimbol)=*(charSet+*(nextNumberIncharset+positionOfSimbol));
                *(nextNumberIncharset+positionOfSimbol)+=1;
                break;                
            }else{ 
                *(curentPassword+positionOfSimbol)=*charSet;
                *(nextNumberIncharset+positionOfSimbol)=1;  
            }
        }   
    }while(positionOfSimbol<maxPasswordLength);
    
//if no match print "no craked"    
printf("no craked\n");
return 0;
}
