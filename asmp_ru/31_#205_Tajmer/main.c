#include <stdio.h>
#include <stdlib.h>

int main() {
    int timeHour, timeMin, timeSec;
    int hour, min, sec;
    int day;
    scanf("%u:%u:%u", &timeHour, &timeMin, &timeSec);
    int intHour, intMin, intSec;
    intHour = intMin = intSec = -1;
    scanf("%u:%u:%u", &intHour, &intMin, &intSec);
    if(intSec < 0 && intMin < 0) {
        intSec = intHour;
        intHour = intMin = 0;
    } else if(intSec < 0) {
        intSec = intMin;
        intMin = intHour;
        intHour = 0;
    }
    day = intHour / 24;
    intHour = intHour % 24;
    sec = (timeSec + intSec) % 60;
    min = (timeMin + intMin + (timeSec + intSec) / 60) % 60;
    hour = intHour + timeHour + (timeMin + intMin + (timeSec + intSec) / 60) / 60;
    day = hour / 24;
    hour = hour % 24;
    printf("%02i:%02i:%02i", hour, min, sec);
    if(day) {
        printf("+%i Days", day);
    }
    printf("\n");
    return 0;
}

