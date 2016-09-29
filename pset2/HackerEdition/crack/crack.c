#define _XOPEN_SOURCE
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, char* argv[]) { 
    //check the arguments
    if (argc<2||argc>4) {
        printf("Usage: ./crack hashedPassword [maxPasswordLength or -da for dictionary attak] [GharSet or dictionary file name]\n");
        return 1;
    }
    
    const char* DEFAULT_CHARSET="ASC2AlfabetSimbol.txt";
    const char* DEFAULT_DICTIONARY="passwords_dictionary_2026318.txt";
    int dictionaryAttak=0;
    FILE* csOrDictFile=NULL;
    int maxPasswordLength=4;
     
    //read and check optional arguments if there are   
    if (argc>2){
        //if the third argument is not a file
        if(!(csOrDictFile=fopen(argv[2], "rb"))){
            //check for a dictionary attack
            if (strcmp(argv[2], "-da")){
                //is not read it as a number
                maxPasswordLength= atoi(argv[2]);
                if (!maxPasswordLength){
                    printf("Usage: ./crack hashedPassword [maxPasswordLength or -da for dictionary attak] [GharSet or dictionary file name]\n");
                    return 1;
                }
            }else {
            maxPasswordLength=255;
            dictionaryAttak=1;
            }
            
            //if the fourth is trying to open the file
            if (argc==4){
                if(!(csOrDictFile=fopen(argv[3], "rb"))){ 
                    printf("Usage: ./crack hashedPassword [maxPasswordLength or -da for dictionary attak] [GharSet or dictionary file name]\n");
                    return 1;
                }
            }  
        }
    }
   
     
    //if no charsetFile open default
    if(!csOrDictFile){
        if (dictionaryAttak){
            if(!(csOrDictFile=fopen(DEFAULT_DICTIONARY, "rb"))){ 
                printf("File open error\n");
                return 1;
            }
        }else{
            if(!(csOrDictFile=fopen(DEFAULT_CHARSET, "rb"))){ 
                printf("File open error\n");
                return 1;
            }
        }
    }
    
    //register is interpreted as "access needs to speed up" depends on the compiler  
    register char* hashedPassword = argv[1];
    register char* curentHashedPassword;
    register char* tmp;
    char salt[3];
    //arrays for password to compare     
    char curentPassword[maxPasswordLength+1];
    //variable for read from file
    unsigned char simbol;
    //curentPassword initialization
    for(int i=0; i<=maxPasswordLength; i++) {
        curentPassword[i]=0;
    }
         
    //extract salt from hashedPassword
    for(int i=0; i<2; i++){ 
        salt[i]=hashedPassword[i];
    }
    salt[2]=0;
   
    if(dictionaryAttak){
        int simbolCounter=0;
        int endofLine=1;
        while(fread(&simbol, 1, 1, csOrDictFile)){
            if (simbol==0x0a || simbol==0x0d) {
                if (endofLine){
                    curentPassword[simbolCounter]=0;
                    simbolCounter=0;
                    endofLine=0;
                    //as the pointer moves assign its value to a temporary variable
                    tmp=hashedPassword;
                    //encrypted current password
                    curentHashedPassword=crypt(curentPassword, salt); 
                    //this blosk of code compare two string (curentHashedPassword and hashedPassword) 
                    //for speed, we avoid call function strcmp
                    while (*curentHashedPassword==*tmp) {
                        if (!(*tmp)){
                            //when the coincidence output current password
                            fclose(csOrDictFile);
                            printf("%s\n", curentPassword);
                            return 0;
                        }
                        tmp++;
                        curentHashedPassword++;
                    }
               }      
            }else{
                curentPassword[simbolCounter]=simbol;
                simbolCounter++;
                endofLine=1;   
            }   
        }
    fclose(csOrDictFile);
    }else{
        //charset array
        char charSet[128];
        //charset array initialization
        for(int i=0; i<128; i++){
            charSet[i]=0;
         }
        // read simbols from file (!! file mast have UNIX end Line) and write in charset array 
        for(int i=0;  fread(&simbol, 1, 1, csOrDictFile);){
            //not read more 127 simbols
            if (simbol!=0x0a && i<128) {
                charSet[i]=simbol;
                i++;
            }       
        }     
        fclose(csOrDictFile);
    
        //arrays for number curent simbols from charset in password
        int nextNumberIncharset[maxPasswordLength+1];
        //nextNumberIncharset initialization
        for(int i=0; i<=maxPasswordLength; i++) {
            nextNumberIncharset[i]=0;
        }
    
        //set first password to compare  
        curentPassword[0]=charSet[0];
        nextNumberIncharset[0]=1;
    
        //register is interpreted as "access needs to speed up" depends on the compiler   
        register int positionOfSimbol;
           
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
    }
        
//if no match print "no craked"    
printf("no craked\n");
return 0;
}
