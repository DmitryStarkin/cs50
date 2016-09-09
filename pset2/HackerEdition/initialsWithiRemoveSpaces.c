#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>

/*
Remove begin spaces from line and move head pointer to first non space simbol
*/
char* RemovBeginSpacesMP(char* line);

/*
Remove begin spaces from line
*/
void RemovBeginSpaces(char* line);

/*
Remove end spaces from line 
*/
void RemovEndSpaces(char* line);

/*
Remove extra spaces from line (leave one space everywhere)
*/
void RemovExtraSpaces(char* line);

/*
Remove All spaces from line
*/
void RemovAllSpaces(char* line);

int main(void) {
    int FirstLeterFlag=1;
    
    string name = GetString();
    
    RemovBeginSpaces(name);
    RemovExtraSpaces(name);
    RemovEndSpaces(name);
    
    for (int i=0, len=strlen(name); i<len; i++) {
        if (isalpha(name[i]) && FirstLeterFlag) {
            printf("%c", toupper(name[i]));
            FirstLeterFlag=0;
        } else if (isblank(name[i]) && !FirstLeterFlag) FirstLeterFlag=1;   
    }
    printf("\n");
}

char* RemovBeginSpacesMP(char* line){
   
    for(;*line==32;line++);
return line;
}

void RemovBeginSpaces(char* line){
    char* tmp=RemovBeginSpacesMP(line);

        if(tmp-line){
            for(int diff=tmp-line; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }        
}

void RemovExtraSpaces(char* line){

    for (char *tmp; *line; line++){
        if (*line==32 && *(line+1)==32){
            tmp=RemovBeginSpacesMP(line);
            for(int diff=tmp-line-1; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }
    }       
}

void RemovAllSpaces(char* line){

    for (char *tmp; *line; line++){
        if (*line==32){
            tmp=RemovBeginSpacesMP(line);
            for(int diff=tmp-line; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }
    }       
}

void RemovEndSpaces(char* line){

    for(;*line;line++);
    line--;
    for(;*line==32;line--) *line=0;
}


