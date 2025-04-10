// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int no_words = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 20011;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    int len = strlen(word);

    while (cursor != NULL)
    {
        // First check lengths, then compare characters without using strcasecmp
        if (strlen(cursor->word) == len)
        {
            int i = 0;
            for (; i < len; i++)
            {
                if (toupper(cursor->word[i]) != toupper(word[i]))
                {
                    break;
                }
            }
            if (i == len)
            {
                return true;
            }
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    unsigned long hash_value = 5381;
    int c;
    while ((c = *word++))
    {
        hash_value = ((hash_value << 5) + hash_value) + toupper(c); // hash * 33 + c
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Cannot open dictionary\n");
        return false;
    }

    char buffer[LENGTH + 1];
    while (fscanf(dict_file, "%45s", buffer) != EOF)
    {
        // Allocate memory for a new word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            fclose(dict_file);
            return false;
        }

        // Insert the word
        strcpy(new_word->word, buffer);

        // Find the corresponding bucket
        int hash_value = hash(buffer);

        // Insert the node into the hash table
        new_word->next = table[hash_value];
        table[hash_value] = new_word;

        // Increase the word count
        no_words++;
    }

    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return no_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
