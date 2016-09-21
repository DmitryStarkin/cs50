#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>
#include<stdlib.h>

int main(int argc, string argv[]) {
    if (argc!=2) {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    
    string keyword = argv[1];
    
    for (int i=0, len=strlen(keyword); i<len; i++){
        if (!isalpha(keyword[i])) {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }
    printf("plaintext: ");
    string text = GetString();
    printf("ciphertext: ");
    for (int i=0, counter=0, key, len=strlen(text); i<len; i++) {
        if (isalpha(text[i])){
            if (counter==strlen(keyword)) counter=0;
            if (isupper(keyword[counter])) key=(int) keyword[counter]-65;
            else key=(int) keyword[counter]-97;
            if (isupper(text[i]))printf("%c", (((text[i]-64)+key)%26)+64);
            else printf("%c", (((text[i]-96)+key)%26)+96);
            counter++;
        }else printf("%c", text[i]);
    }
printf("\n");
return 0;
}
