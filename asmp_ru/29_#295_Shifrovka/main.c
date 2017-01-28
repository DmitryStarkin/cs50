#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char line[41];
    char word[41];
    scanf("%s", line);
    scanf("%s", word);
    char targetline[41];
    char wordToCompare[41];
    for(int i = 0; i < 26; i++) {
        for(int y = 0; y < strlen(line); y++) {
            targetline[y] = (line[y] - 'A' + i) % 26 + 'A';
        }
        targetline[strlen(line)] = '\0';
        for(int y = 0; y <= strlen(targetline) - strlen(word); y++) {
            for(int k = y, j = 0; j < strlen(word); k++, j++) {
                wordToCompare[j] = targetline[k];
            }
            wordToCompare[strlen(word)] = '\0';
            if(!strcmp(word, wordToCompare)) {
                printf("%s", targetline);
                return 0;
            }
        }
    }
    printf("IMPOSSIBLE");
    return 0;
}
