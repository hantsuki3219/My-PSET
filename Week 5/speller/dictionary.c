// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// declare variables
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *cursor = table[index];

    // loop word in bucket
    while(cursor != NULL)
    {
        // compare
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    //return tolower(word[0]) - 'a';
    unsigned long total = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the fckn dic
    FILE *file = fopen(dictionary, "r");

    // return NULL if cnt open
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return false;
    }
    // buffer for word +1 for \0
    char word[LENGTH + 1];

    // scan and read word
    while(fscanf(file, "%s", word) != EOF)
    {
        // allocate new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Unable to create new node\n");
            return false;
        }

        // copy word into node and set next to NULL
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // find bucket for hash
        unsigned int index = hash(word);

        // if bucket empt
        if(table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }

        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // loop bucket
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    //return false;
    return true;
}
