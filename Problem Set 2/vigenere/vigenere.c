#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

//Check just one word 
    if (argc != 2)
    {   
        printf("Usage: ./vigenere keyword\n");
        exit(1);
    }
//delcare key
    string key = argv[1];
    int shift[strlen(key)];
//Check all keyword are chars AND store shift values in array  
    int n = 0;
    while (key[n] != '\0')
    {
        if (islower(key[n])) 
        {
            shift[n] = key[n] - 97;        
        }
        else if (isupper(key[n]))
        {
            shift[n] = key [n] - 65; 
        }
        else
        {
            printf("Usage: ./vigenere keyword\n");  
            exit(1);  
        }
        n++;
    }      
//get plaintext
    string plaintext = get_string("Plaintext:");
    unsigned char codetext[strlen(plaintext)];
    n = 0;
    int m = 0;
    while (plaintext[n] != '\0')
    {
        //make key repeat
        if (m == strlen(key))
        {
            m = 0;
        }
        if (isalpha(plaintext[n]))
        {
            codetext[n] = plaintext[n] + shift[m];
            m++;
            //capitals
            if (plaintext[n] < 91 && codetext[n] > 90) 
            {
                codetext[n] = (codetext[n] - 90) + 64;
            }
            //lowercase
            else if (plaintext[n] > 96 && codetext[n] > 122)
            {
                codetext[n] = (codetext[n] - 122) + 96;
            }
        }
        else
        {
            codetext[n] = plaintext[n];
        }
        n++;
    }
    printf("ciphertext: ");
    for (int k = 0; k < strlen(plaintext); k++)
    {
        printf("%c", codetext[k]);
    }
    printf("\n");
}