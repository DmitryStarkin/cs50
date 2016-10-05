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
    bool isWord;
    struct contayner *children[27];
};
typedef struct contayner node;
node *root;
unsigned int sizeOfDicinary=0;
    
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {
    
    // TODO
    register node *curentNode=root;
    register int index;
   
    for(; *word; word++) {
        index = (*word==39) ? 26:tolower(*word)-97;
        if (!curentNode->children[index]) {
            return false;
        }
        curentNode=curentNode->children[index];
    }
    if(curentNode->isWord) {
        return true;
    } 
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary) {
    
    // TODO
    uint8_t simbol;
    root=calloc(1, sizeof(node));
    register node *curentNode=root;
    register int index;

    // open dictionary file
    FILE* dctionaryFile = fopen(dictionary, "rb");
    if (dctionaryFile == NULL){
        return false;
    }

    // read from file and add word to memory 
    while(fread(&simbol, 1, 1, dctionaryFile)) { 
        if (simbol==0x0a) {
            curentNode->isWord=true;
            curentNode=root;
            sizeOfDicinary++;
        } else {
            index=(simbol==39) ? 26:simbol-97;
            if (!curentNode->children[index]) {
                curentNode->children[index]=calloc(1, sizeof(node));
            }
            curentNode=curentNode->children[index];
        }
    }  
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
 * Unloads contayners from memory.
 */

void freeContayner(register node *curentNode) {
    for (register int i=0; i<27; i++) {
        if (curentNode->children[i]) freeContayner(curentNode->children[i]);
    }
    free(curentNode);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void) {
    
    // TODO
    freeContayner (root);
      
    return true;
}
