#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int grNum = 0;
    int rainTime = 0;

    scanf("%i", &grNum);
    scanf("%i", &rainTime);

    int gribs[grNum][3];
    for (int i = 0; i < grNum; i++){
        for (int y = 0; y < 3 ; y++){
            scanf("%i", &gribs[i][y]);
        }
    }

    double minDist = 0;
    double dist = 0;
    for (int i = 0; i < grNum; i++){
        for (int y = i + 1; y < grNum; y++){
            dist = sqrt (pow ((gribs[i][0] - gribs[y][0]), 2) + pow ((gribs[i][1] - gribs[y][1]), 2)) - gribs[i][2] - gribs[y][2];
            if (dist < minDist || i == 0){
                minDist = dist;
            }
        }
    }
    double delta = (double) rainTime*2;
    if (delta <= minDist) {
        printf ("%1.2f", (double) rainTime);
    } else{
        printf ("%1.2f", minDist/2);
    }
    return 0;
}