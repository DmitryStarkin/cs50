#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void) {
    char str[1001];
    fgets(str, 1001, stdin);
    if (str[strlen(str)-1] != '\n') {
        str[strlen(str)] = '\n';
        str[strlen(str)+1] = '\0';
    }

    char *tmp = str;
    char first[3];
    char second[3];
    char *tFirst = first;
    char *tSecond = second;
    int flag = 0;

    if (isdigit(*tmp) || islower(*tmp)){
      printf("NO");
      return 0;
    }

    for (; *tmp; tmp++){
        if (isalpha(*tmp)|| *tmp == '\n'){
            if (isupper(*tmp)|| *tmp == '\n'){
                flag++;
            }
            if (flag == 1){
                *tFirst = *tmp;
                tFirst++;
            } else if(flag == 2) {
                    *tFirst = '\0';
                    *tSecond = *tmp;
                    tSecond++;
                    } else {
                    *tSecond = '\0';
                        if (!strcmp(first, second)){
                            printf("NO");
                            return 0;
                        }
                        tFirst = first;
                        tSecond = second;
                        flag = 0;
                        if (*tmp == '\n'){
                        break;
                        }
                        tmp--;
                    }
        }
    }

    printf("YES");
    return 0;
}