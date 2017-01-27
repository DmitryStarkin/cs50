#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int workTimes(int* date) {
    int time;
    switch(date[0]) {
    case 1:
        time = (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3];
        break;
    case 2:
        time = 31 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 3:
        time = 60 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 4:
        time = 91 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 5:
        time = 121 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 6:
        time = 152 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 7:
        time = 182 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 8:
        time = 213 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 9:
        time = 244 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 10:
        time = 274 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 11:
        time = 305 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    case 12:
        time = 335 * 480 + (date[1] - 1) * 480 + (date[2] - 10) * 60 + date[3] + 2;
        break;
    }
    return time;
}

int main() {
    int tasks;
    scanf("%i", &tasks);
    scanf("%*c");
    char* task[tasks];
    char tmp1, tmp2;
    for(int i = 0; i < tasks; i++) {
        task[i] = malloc(sizeof(char) * 14);
        fgets(task[i], 14, stdin);
        task[12] = '\0';
        tmp1 = task[i][0];
        tmp2 = task[i][1];
        task[i][0] = task[i][3];
        task[i][1] = task[i][4];
        task[i][3] = tmp1;
        task[i][4] = tmp2;
    }
    int flag = 1;
    char* tmp3;
    while(flag) {
        flag = 0;
        for(int i = 0, y = 1; y < tasks; i++, y++) {
            if(strcmp(task[i], task[y]) > 0) {
                tmp3 = task[i];
                task[i] = task[y];
                task[y] = tmp3;
                flag = 1;
            }
        }
    }
    int workTime = 0;
    int timesstart[4];
    int timesend[4];
    for(int i = 0, y = 1; y < tasks; i += 2, y += 2) {
        sscanf(task[i], "%u.%u.%u:%u", &timesstart[0], &timesstart[1], &timesstart[2], &timesstart[3]);
        sscanf(task[y], "%u.%u.%u:%u", &timesend[0], &timesend[1], &timesend[2], &timesend[3]);
        workTime += workTimes(timesend) - workTimes(timesstart);
    }
    printf("%i:%02i\n", workTime / 60, workTime % 60);
    for(int i = 0; i < tasks; i++) {
        free(task[i]);
    }
    return 0;
}
