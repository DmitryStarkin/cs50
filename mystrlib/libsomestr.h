#ifndef _LIBSOMESTR_H
#define _LIBSOMESTR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
Remove begin spaces from string and move head pointer to first non space simbol
*/
char* removBeginSpacesMP(char* line);

/**
Remove begin spaces from string
*/
void removBeginSpaces(char* line);

/**
Remove end spaces from string 
*/
void removEndSpaces(char* line);

/**
Remove extra spaces from string (leave one space everywhere)
*/
void removExtraSpaces(char* line);

/**
Remove All spaces from string
*/
void removAllSpaces(char* line);

/**
Reverses the string in place
*/
void inverseString(char* string);

/**
read string from file  (need free after usage)
*/
char* readString(FILE* inFile);

#endif