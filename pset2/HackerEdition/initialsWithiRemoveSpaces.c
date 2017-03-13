#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>

/*
Remove begin spaces from line and move head pointer to first non space simbol
*/
char* removBeginSpacesMP(char* line);

/*
Remove begin spaces from line
*/
void removBeginSpaces(char* line);

/*
Remove end spaces from line
*/
void removEndSpaces(char* line);

/*
Remove extra spaces from line (leave one space everywhere)
*/
void removExtraSpaces(char* line);

/*
Remove All spaces from line
*/
void removAllSpaces(char* line);

int main(void) {
    int firstLeterFlag = 1;
    string name = GetString();
    removBeginSpaces(name);
    removExtraSpaces(name);
    removEndSpaces(name);
    for(int i = 0, len = strlen(name); i < len; i++) {
        if(isalpha(name[i]) && firstLeterFlag) {
            printf("%c", toupper(name[i]));
            firstLeterFlag = 0;
        } else if(isblank(name[i]) && !firstLeterFlag) firstLeterFlag = 1;
    }
    printf("\n");
}

char* removBeginSpacesMP(char* line) {
    for(; *line == 32; line++);
    return line;
}

void removBeginSpaces(char* line) {
    char* tmp = removBeginSpacesMP(line);
    if(tmp - line) {
        for(int diff = tmp - line; * (tmp - 1); tmp++) {
            *(tmp - diff) = *tmp;
        }
    }
}

void removExtraSpaces(char* line) {
    for(char *tmp; *line; line++) {
        if(*line == 32 && *(line + 1) == 32) {
            tmp = removBeginSpacesMP(line);
            for(int diff = tmp - line - 1; * (tmp - 1); tmp++) {
                *(tmp - diff) = *tmp;
            }
        }
    }
}

void removAllSpaces(char* line) {
    for(char *tmp; *line; line++) {
        if(*line == 32) {
            tmp = removBeginSpacesMP(line);
            for(int diff = tmp - line; * (tmp - 1); tmp++) {
                *(tmp - diff) = *tmp;
            }
        }
    }
}

void removEndSpaces(char* line) {
    for(; *line; line++);
    line--;
    for(; *line == 32; line--) *line = 0;
}


