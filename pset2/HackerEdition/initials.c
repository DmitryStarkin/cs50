#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>

int main(void) {
    int FirstLeterFlag=1;
    string name = GetString();
    
    for (int i=0, len=strlen(name); i<len; i++) {
        if (isalpha(name[i]) && FirstLeterFlag) {
            printf("%c", toupper(name[i]));
            FirstLeterFlag=0;
    } else if (isblank(name[i]) && !FirstLeterFlag) FirstLeterFlag=1;   
}
    printf("\n");
}
