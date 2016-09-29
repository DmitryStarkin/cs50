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
bool search(int value, int values[], int n){
    // TODO: implement a searching algorithm
   if (n<0) return false; 
   int key=n/2;
        do { 
            n=n/2;
            if (values[key] == value){
                return true;
            }
            if (values[key] > value){
                key=key-n/2-1;
            }
            else{ 
                key=key+(n+1)/2;
            }
        } while(n);  
   return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n){
    // TODO: implement an O(n^2) sorting algorithm
    int changeFlag, tempValue;
    do {
        changeFlag = 0;
        for (int i=1, j=0; i<n; i++, j++){
            if (values[j] > values[i]){
                tempValue = values[i];
                values[i] = values[j];
                values[j] = tempValue;
                changeFlag = 1;
            }
        }
    } while (changeFlag);
}
