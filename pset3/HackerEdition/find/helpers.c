/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {
    // TODO: implement a searching algorithm
    if(n < 0) return false;
    int key = n / 2;
    do {
        n = n / 2;
        if(values[key] == value) return true;
        if(values[key] > value) key = key - n / 2 - 1;
        else key = key + (n + 1) / 2;
    } while(n);
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {
    // TODO: implement an O(n) sorting algorithm
    //counting sorting, the algorithm is taken from http://programador.ru/sorting-positive-int-linear-time/
    int minValue, maxValue;
    minValue = maxValue = values[0];
    for(int i = 0; i < n; i++) {
        if(values[i] < minValue) {
            minValue = values[i];
        }
        if(values[i] > maxValue) {
            maxValue = values[i];
        }
    }
    int count[maxValue - minValue + 1];
    for(int i = 0, len = maxValue - minValue + 1; i < len; i++) {
        count[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        count[values[i] - minValue]++;
    }
    for(int i = 0, valuesIndex = 0, len = maxValue - minValue + 1; i < len; i++) {
        for(int y = 0; y < count[i]; y++) {
            values[valuesIndex++] = i + minValue;
        }
    }
}
