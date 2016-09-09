#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>


char* RemovExtraSpaces(char* line);
char* RemovBeginSpaces(char* line);

int main(void) {
    int FirstLeterFlag=1;
    
    string name = GetString();
    
    name = RemovExtraSpaces(name);
    
    for (int i=0, len=strlen(name); i<len; i++) {
        if (isalpha(name[i]) && FirstLeterFlag) {
            printf("%c", toupper(name[i]));
            FirstLeterFlag=0;
    } else if (isblank(name[i]) && !FirstLeterFlag) FirstLeterFlag=1;   
}
    printf("\n");
}


char* RemovBeginSpaces(char* line){
    for(;*line==32;line++);
return line;
}

char* RemovExtraSpaces(char* line){
char *tmp1;

    line = RemovBeginSpaces(line);
    tmp1=line;
    
    for (char *tmp2; *tmp1; tmp1++){
        if (*tmp1==32 && *tmp1+1==32){
            tmp2=RemovBeginSpaces(tmp1+1);
            for(int diff=tmp2-tmp1; *(tmp2-1); tmp2++){
                *(tmp2-diff)=*tmp2;
            }
        }
    } 
    if (*(tmp1-1)==32) *(tmp1-1)=0;   
return line;    
}
