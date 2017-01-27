#include <stdio.h>
#include <stdlib.h>

int main() {
    int numberOfWord;
    scanf("%i", &numberOfWord);
    char *word = malloc(sizeof(char) * 30001);
    char *tmp = word;
    int zero;
    int one;
    int two;
    int curChar;
    int yes;
    for (int i = 0; i < numberOfWord; i++ ) {
        scanf("%s", word);
        tmp = word;
        zero = one = two = 0;
        yes = 1;
            for(; *tmp; tmp++) {
                curChar = *tmp - 48;
                switch (curChar) {
                case 0:
                    if (one || two) {
                        yes = 0;
                        break;
                    }
                    zero++;
                    break;
                case 1:
                    if(two) {
                        yes = 0;
                        break;
                    }
                    one++;
                    break;
                case 2:
                    two++;
                    break;
                }
                if(!yes) {
                    break;
                }
            }

        if (yes && (zero == one) && (one== two)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        free(word);
        return 0;
    }
}
