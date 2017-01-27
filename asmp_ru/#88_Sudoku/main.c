#include <stdio.h>
#include <stdlib.h>



void clearValidator(int* validator, int size) {
    for(int i = 0; i < size; i++) {
        validator[i] = 0;
    }
}

int isValid(int* validator, int size) {
    for(int i = 0; i < size; i++) {
        if(!validator[i]) {
            return 0;
        }
    }
    return 1;
}


int main() {
    int size;
    scanf("%u", &size);
    int sideSize = size * size;
    int nums[sideSize][sideSize];
    for(int i = 0; i < sideSize; i++) {
        for(int y = 0; y < sideSize; y++) {
            scanf("%u", &nums[i][y]);
        }
    }
    int validator1[sideSize];
    clearValidator(validator1, sideSize);
    int validator2[sideSize];
    clearValidator(validator2, sideSize);
    for(int i = 0; i < sideSize; i++) {
        for(int y = 0; y < sideSize; y++) {
            validator1[nums[i][y] - 1]++;
            validator2[nums[y][i] - 1]++;
        }
        if(!isValid(validator1, sideSize) || !isValid(validator2, sideSize)) {
            printf("Incorrect\n");
            return 0;
        }
        clearValidator(validator1, sideSize);
        clearValidator(validator2, sideSize);
    }
    for(int i = 0; i < sideSize; i += size) {
        for(int y = 0; y < sideSize; y += size) {
            for(int k = i; k < i + size; k++) {
                for(int j = y; j < y + size; j++) {
                    validator1[nums[k][j] - 1]++;
                }
            }
            if(!isValid(validator1, sideSize)) {
                printf("Incorrect\n");
                return 0;
            }
            clearValidator(validator1, sideSize);
        }
    }
    printf("Correct\n");
    return 0;
}
