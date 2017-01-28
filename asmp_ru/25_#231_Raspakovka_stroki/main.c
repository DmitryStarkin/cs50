#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char line[81];
    scanf("%s", line);
    char num[3];
    num[0] = '1';
    int strleng = 0;
    int nonum = 1;
    for(int i = 0, y = 0; i < strlen(line); i++) {
        if(isdigit(line[i])) {
            num[y] = line[i];
            y++;
            nonum = 0;
        } else {
            num[y + nonum] = '\0';
            for(int k = 0; k < atoi(num); k++) {
                if(strleng == 40) {
                    printf("\n");
                    strleng = 0;
                }
                printf("%c", line[i]);
                strleng++;
            }
            y = 0;
            num[0] = '1';
            nonum = 1;
        }
    }
}
