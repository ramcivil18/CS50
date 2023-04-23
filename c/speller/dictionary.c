// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int words = 0;
unsigned int hash_key;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_key = hash(word);
    node *temp = table[hash_key];
    while (temp != 0)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;

        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i =0; i < strlen(word);i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *input = fopen(dictionary, "r");

    if (input == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];


    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        hash_key = hash(word);
        n->next = table[hash_key];
        table[hash_key] = n;
        words++;

    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words;
}

void freenode(node *n)
{
    if(n->next != NULL)
    {
        freenode(n->next);
    }
    free(n);
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {

        if (table[i] != NULL)
        {
            freenode(table[i]);
        }

    }
    return true;
}
