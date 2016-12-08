/**
 * Implements a somestr functionality.
 */

#include "libsomestr.h"

/**
Initial memory size and the magnification ratio
*/
const int MEM_MULT = 2;
const int INITIAL_BIT = 15;

char* removBeginSpacesMP(char* line){
   
    for(;*line==32;line++);
return line;
}

void removBeginSpaces(char* line){
    char* tmp=removBeginSpacesMP(line);

        if(tmp-line){
            for(int diff=tmp-line; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }        
}

void removExtraSpaces(char* line){

    for (char *tmp; *line; line++){
        if (*line==32 && *(line+1)==32){
            tmp=removBeginSpacesMP(line);
            for(int diff=tmp-line-1; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }
    }       
}

void removAllSpaces(char* line){

    for (char *tmp; *line; line++){
        if (*line==32){
            tmp=removBeginSpacesMP(line);
            for(int diff=tmp-line; *(tmp-1); tmp++){
                *(tmp-diff)=*tmp;
            }
        }
    }       
}

void removEndSpaces(char* line){

    for(;*line;line++);
    line--;
    for(;*line==32;line--) *line=0;
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
        retMem = realloc(string, memSize * sizeof(char));
            if(retMem){
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