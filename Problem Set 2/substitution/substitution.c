#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //make sure just one word key
    string key = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    //check all letters
    int i = 0;
    while (key[i] != '\0')
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must contain 26 letters.\n");
            exit(1);
        }
        //turn key all lowercase
        if (isupper(key[i]) != 0)
        {
            key[i] = key[i] + 32;
        }
        i++;
    }
    //check 26 letters
    if (i != 26)
    {
        printf("Key must contain 26 letters.\n");
        exit(1);
    }
    //check no duplicates
    i = 0;
    while (key[i] != '\0')
    {
        int j = i + 1;
        while (key[j] != '\0')
        {

            if (key[j] == key [i])
            {
                printf("Key must contain all 26 letters.\n");
                exit(1);
            }
            j++;
        }
        i++;
    }
    //get plaintext
    string plaintext = get_string("plaintext: ");
    //change plaintext
    i = 0;
     while (plaintext[i] != '\0')
     {
         if (isupper(plaintext[i]) != 0)
         {
             plaintext[i] = key[plaintext[i] - 65] - 32;
         }
         if (islower(plaintext[i]) != 0)
         {
             plaintext[i] = key[plaintext[i] - 97];
         }
         i++;
     }
     //print
    printf("ciphertext: %s\n", plaintext);
    exit(0);


}