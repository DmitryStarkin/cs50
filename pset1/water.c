#include <cs50.h>
#include <stdio.h>

int main(void) {
    const int BOTTLES_PER_MIN = 12;
    int minutes = 0;
    printf("minutes:");
    minutes = GetInt();
    printf("bottles: %d\n", BOTTLES_PER_MIN * minutes);
    return 0;
}
