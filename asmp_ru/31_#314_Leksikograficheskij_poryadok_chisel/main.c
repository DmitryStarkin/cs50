#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int maxnum;
    int targetnum;
    scanf ("%i", &maxnum);
    scanf ("%i", &targetnum);

    char *nums[maxnum];
    for(int i = 1, j = 0, coun = 0; i <= maxnum; i++) {
        nums[i - 1] = malloc(5*sizeof(char));
        j = i;
        coun = 0;
        while(j) {
            *(nums[i - 1] + coun++) = j%10 + 48;
            j = j/10;
        }
        *(nums[i-1] + coun) = '\0';

        char tmp;
        for (int f = 0, y = strlen(nums[i-1])-1, k = (y+1)/2; f < k; f++, y--) {
            tmp = *(nums[i -1]+f);
            *(nums[i-1]+f) = *(nums[i-1]+y);
            *(nums[i-1]+y) = tmp;
        }
    }

    char *tmp;
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 0, j = 1; i < maxnum - 1 ; i++, j++ ) {
            if (strcmp(nums[i], nums[j]) > 0) {
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
                flag = 1;
            }
        }
    }


    for (int i = 0; i < maxnum; i++) {
        if (targetnum == atoi(nums[i])) {
            printf ("%i", i+1);
            break;
        }
    }
    return 0;
}
