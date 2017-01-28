#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



char* removBeginNoAlphaMP(char* line) {
    for(; !isalpha(*line) && (*line != '\0'); line++);
    return line;
}


void removeAllNoAlpha(char* line) {
    for(char *tmp; *line; line++) {
        if(!isalpha(*line)) {
            tmp = removBeginNoAlphaMP(line);
            for(int diff = tmp - line; * (tmp - 1); tmp++) {
                *(tmp - diff) = *tmp;
            }
        }
    }
}

void allToLow(char* line) {
    for(; *line; line++) {
        if(isupper(*line)) {
            *line = tolower(*line);
        }
    }
}

int isPolinom(char* line) {
    for(int i = 0, k = strlen(line), y = k - 1; i < k / 2; i++, y--) {
        if(line[i] != line[y]) {
            return 0;
        }
    }
    return 1;
}

void remoweOneSimbol(char* line, int position) {
    if(!strlen(line) || position > strlen(line) || position < 0) {
        return;
    }
    if(line [position + 1] == '\0') {
        line[position] = '\0';
        return;
    }
    for(int i = position, y = position + 1; y < strlen(line); i++, y++) {
        line[i] = line[y];
    }
    line[strlen(line)-1] = '\0';
}

char* insertOneSimbol(char* line, char simbol, int position) {
    line = realloc(line, strlen(line) + 2);
    line[strlen(line) + 1] = '\0';
    if(line [position] == '\0') {
        line[position] = simbol;
        return line;
    }
    for(int i = strlen(line); i > position; i--) {
        line[i] = line[i - 1];
    }
    line[position] = simbol;
    return line;
}

int main() {
    char  tmp;
    char *string = malloc(sizeof(char) * 100001);
    fgets(string, 100001, stdin);
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }
    removeAllNoAlpha(string);
    allToLow(string);
    for(int i = 0, error = 0, k = strlen(string), y = k - 1; i < k / 2; i++, y--) {
        if(string[i] != string[y]) {
            error++;
            if(error > 1) {
                printf("NO\n");
                return 0;
            }
            tmp = string[i];
            string[i] = string[y];
            if(isPolinom(string)) {
                continue;
            }
            string[i] = tmp;
            remoweOneSimbol(string, i);
            if(isPolinom(string)) {
                k = strlen(string);
                y--;
                continue;
            }
            string = insertOneSimbol(string, tmp, i);
            tmp = string[y];
            remoweOneSimbol(string, y);
            if(isPolinom(string)) {
                k = strlen(string);
                y--;
                continue;
            }
            string = insertOneSimbol(string, tmp, y);
            string = insertOneSimbol(string, string[y], i);
            if(isPolinom(string)) {
                k = strlen(string);
                y++;
                continue;
            }
            remoweOneSimbol(string, i);
            string = insertOneSimbol(string, string[i], y);
            if(isPolinom(string)) {
                k = strlen(string);
                continue;
            }
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    printf("%s\n", string);
    free(string);
    return 0;
}
