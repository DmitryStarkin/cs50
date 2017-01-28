#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void nanums(int *spis, int pos) {
    int curpos = 0;
    int curnum = 2;
    while (pos!=curpos) {
        int del = 0;
        for (int i = 1, k; i <= curnum; i++ ) {
            k  =  curnum%i;
            if (!k) {
                del++;
            }
            if (del > 2) {
                break;
            }
        }
        if (del <= 2) {
            int tmp = curnum;
            char tmps[10];
            int count=0;
            while (tmp) {
                tmps[count++] = tmp%10 + 48;
                tmp = tmp/10;
            }
            tmps[count]='\0';
            char tmpchar;
            for (int i = 0, y = strlen(tmps)-1, k=(y+1)/2; i<k; i++, y--) {
                tmpchar=tmps[i];
                tmps[i]=tmps[y];
                tmps[y]=tmpchar;
            }
            for (int i = 0, y = strlen(tmps); i<y; i++ ) {
                curpos++;
                spis[curpos] = tmps[i] - 48;
                if (curpos == pos) {
                    break;
                }
            }
        }
        del = 0;
        curnum++;
    }


}
int main() {
    int tests;
    scanf("%i", &tests);

    int pos[tests];
    int maxpos=0;
    for (int i =0; i < tests; i++) {
        scanf("%i", pos+i);
        if (pos[i]> maxpos) {
            maxpos = pos[i];
        }
    }



    int spis[maxpos + 1];

    nanums(spis, maxpos);
    for (int i = 0; i < tests; i++) {
        printf("%i", spis[pos[i]]);
    }

    return 0;

}
