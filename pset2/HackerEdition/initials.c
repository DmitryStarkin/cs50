#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>

int main(void) {
    int firstLeterFlag=1;
    string name = GetString();
    
    for (int i=0, len=strlen(name); i<len; i++) {
        if (isalpha(name[i]) && firstLeterFlag) {
            printf("%c", toupper(name[i]));
            firstLeterFlag=0;
    } else if (isblank(name[i]) && !firstLeterFlag) 
            firstLeterFlag=1;   
    }
    printf("\n");
}
