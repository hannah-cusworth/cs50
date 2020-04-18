#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, string argv[])
{
    //get string
    string text = get_string("Text: ");
    //define measures
    float letters = 0;
    float words = 1;
    float sentences = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        //count letters
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
        // count words
        if (text[i] == 32)
        {
            words++;
        }
        //count sentences
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
        i++;
    }
    //calculate L and S
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    //index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //print
    if (index > 16)
    {
        printf("Grade 16+\n");
        exit(0);
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
        exit(0);
    }
    else
    {
        int index2 = round(index);
        printf("Grade %i\n", index2);
        exit(0);
    }
}