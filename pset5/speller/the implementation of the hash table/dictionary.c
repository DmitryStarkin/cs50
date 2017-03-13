/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

struct contayner {
    char *word;
    struct contayner *next;
};
typedef struct contayner wordContayner;
typedef wordContayner *pointerToWord;

pointerToWord *hashTable;
unsigned int sizeOfDicinary = 0;
unsigned int indexOfHashTable = 0x3ffff;
int sizeFaktor = 14;
char curentWord[LENGTH];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {
    // TODO
    //the hash function algorithm is taken from https://habrahabr.ru/post/219139/
    register char  *tmp,  *tmp1;
    register unsigned int hash = 0;
    register pointerToWord head;
    tmp = curentWord;
    for(; *word; word++, tmp++) {
        *tmp = tolower(*word);
        hash = ((hash * 1664525) + (unsigned char)(*tmp) + 1013904223);
    }
    hash = hash >> sizeFaktor;
    *tmp = 0x00;
    head = *(hashTable + hash);
    if(!head) {
        return false;
    }
    do {
        tmp = head->word;
        tmp1 = curentWord;
        while(*tmp == *tmp1) {
            if(!(*tmp)) return true;
            tmp++;
            tmp1++;
        }
        if((*tmp - *tmp1) < 0) {
            return false;
        }
        head = head->next;
    } while(head);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary) {
    // TODO
    //the hash function algorithm is taken from https://habrahabr.ru/post/219139/
    uint8_t simbol;
    register char *curentWord;
    register int counter = 0;
    register unsigned int hash = 0;
    register pointerToWord newWord;
    FILE* dctionaryFile = fopen(dictionary, "rb");
    if(dctionaryFile == NULL) {
        return false;
    }
    // give memory for hashtable
    while(!(hashTable = calloc(indexOfHashTable + 1, sizeof(pointerToWord)))) {
        indexOfHashTable = indexOfHashTable >> 1;
        if(indexOfHashTable < 0xff) return false;
        sizeFaktor++;
    }
    curentWord = malloc(LENGTH);
    while(fread(&simbol, 1, 1, dctionaryFile)) {
        if(simbol == 0x0a) {
            *(curentWord + counter) = 0x00;
            sizeOfDicinary++;
            hash = hash >> sizeFaktor;
            ++counter;
            newWord = malloc(sizeof(wordContayner));
            newWord->word = realloc(curentWord, counter);
            newWord->next = *(hashTable + hash);
            *(hashTable + hash) = newWord;
            counter = 0;
            hash = 0;
            curentWord = malloc(LENGTH);
        } else {
            *(curentWord + counter) = simbol;
            hash = ((hash * 1664525) + (unsigned char)(simbol) + 1013904223);
            counter++;
        }
    }
    free(curentWord);
    fclose(dctionaryFile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {
    // TODO
    return sizeOfDicinary;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void) {
    // TODO
    pointerToWord head, tmph;
    pointerToWord *tmp = hashTable;
    for(unsigned int i = 0, y = indexOfHashTable + 1; i < y; i++, tmp++) {
        head = *tmp;
        if(!head) {
            continue;
        }
        do {
            free(head->word);
            tmph = head;
            head = head->next;
            free(tmph);
        } while(head);
    }
    free(hashTable);
    return true;
}
