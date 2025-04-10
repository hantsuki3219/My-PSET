#include <stdio.h>
#include "cs50.h"

int i,space,sharp,height; //i = round, space = print_space, sharp = print_sharp
void print_space (void);
void print_sharp (void);

int main(void)
{
    do
    {
    height = get_int("Height: ");
    } while (height < 0 || height == 0 || height > 8);
    
    for (i = 1; i <= height; i++) 
    {
        for (space = height; space > i ; space--) 
        {
            print_space();
        }
        for (sharp = 1; sharp <= i; sharp++) 
        {
            print_sharp();
        }
        printf(" ");
        for (sharp = 1; sharp <= i; sharp++) 
        {
            print_sharp();
        }
        printf("\n");
    }

    return (0);
}

void print_sharp (void)
{
    printf("#");
}

void print_space (void)
{
    printf(" ");
}