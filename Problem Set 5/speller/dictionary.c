// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "dictionary.h"
#include <strings.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];
int counter = 0;
//print all of a linked list
void printnode(node *header)
{
    node *current_node = header;
    while (current_node != NULL)
    {
        printf("%s\n", current_node->word);
        current_node = current_node->next;
    }

}
// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int index = hash(word);
    //printf("index: %i\n", index);
    node *current_node = table[index];
    while (current_node != NULL)
    {
        //printf("current node: %s\n word: %s\n", current_node->word, word);
        if (strcasecmp(current_node->word, word) == 0)
        {
            //printf("Yaaaaaas %s\n", word);
            return true;
        }
        current_node = current_node->next;
    }
    //printf("%s ain't here chief\n", word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int w_len = strlen(word);
    long sum = 0;
    for (int i = 0; i < w_len; i++)
    {
        if (isupper(word[i]))
        {
            sum += pow((word[i] + 32), w_len - i);
        }
        else
        {
            sum += pow(word[i], w_len - i);
        }
    }

    return labs((sum * 37) % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    char w[LENGTH];

    int i = 0;
    for (int c = fscanf(file, "%s", w); c != EOF; c = fscanf(file, "%s", w))
    {
        //make new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 2;
        }
        strcpy(n->word, w);
        int ind = hash(w);
        counter++;
        //insert new node
        n->next = table[ind];
        table[ind] = n;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current_node = table[i];
        while (current_node != NULL)
        {
            node *tmp = current_node;
            current_node = current_node->next;
            free(tmp);
        }
    }
    return true;
}