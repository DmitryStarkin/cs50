#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    scanf("%u", &size);
    int nums[size];
    for(int i = 0; i < size; i++) {
        scanf("%i", &nums[i]);
    }
    int maxlen = 0;
    int len = 0;
    for(int i = 0; i < size - 2; i++) {
        if(((nums[i] < nums[i + 1]) && (nums[i + 1] > nums[i + 2])) || ((nums[i] > nums[i + 1]) && (nums[i + 1] < nums[i + 2]))) {
            len++;
        } else {
            len += 2;
            if(len > maxlen) {
                maxlen = len;
            }
            len = 0;
        }
    }
    if(len) {
        len += 2;
    }
    if(!maxlen) {
        maxlen = len;
    }
    printf("%d", maxlen);
}
