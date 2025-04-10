#include <stdio.h>
#include "cs50.h"
#include <ctype.h>
#include <math.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //recieve user text
    string text = get_string("Text: ");

    //count letters, words, sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentences: %i\n", sentences);

    if(words == 0)
    {
        printf("Grade: Before Grade 1\n");
        return 0;
    }
    //coleman index
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    float grade = (0.0588 * L) - (0.296 * S) - 15.8;
    //index = 0.0588 * L - 0.296 * S - 15.8
    //L = average number of letters per 100 words, S is average num of sentences per 100 words in intex
    //print Coleman-Liau index
    printf("L: %.2f\n", L);
    printf("S: %.2f\n", S);
    printf("Index: %.2f\n", grade);
    int rGrade = round(grade);
    //print grade
    if (rGrade >= 16)
    {
        printf("Grade: 16+\n");
    }
    else if(rGrade < 1)
    {
        printf("Grade: Before Grade 1\n");
    }
    else
        printf("Grade: %i\n", rGrade);
    return 0;
}

int count_letters(string text)
{
    int count = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
        count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0, in_word = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(isspace(text[i]))
        {
            in_word = 0;
        }
        else if (in_word == 0)
        {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
        count++;
        }
    }
    return count;
}