#include <stdio.h>
#include "cs50.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    //get key & check argument
    if(argc != 2)
    {
        printf("./caesar key\n");
        return 1;
    }
    //check isdigit
    string key_string = argv[1];
    for(int i = 0; i < strlen(key_string); i++)
    {
        if(!isdigit(key_string[i]))
        {
        printf("./caesar key\n");
        return 1;
        }
    }
    //get text
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    //turn key to int
    int key = atoi(key_string);
    int pt = atoi(plaintext);
    //encrypt
    for(int i = 0; i < strlen(plaintext); i++)
    {
        char a = plaintext[i];
        if(isupper(a))
        {
            char ciphertext = (a - 'A' + key) % 26 + 'A';
            printf("%c", ciphertext);
        }
        else if(islower(a))
        {
            char ciphertext = (a - 'a' + key) % 26 + 'a';
            printf("%c", ciphertext);
        }
        else
        {
            printf("%c", a);
        }

    }
    //output
    printf("\n");
    return 0;
}