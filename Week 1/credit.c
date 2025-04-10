#include <stdio.h>
#include "cs50.h"

int main(void)
{
    //get card num
    long card_num = get_long("Number: ");
    
    int sum_odd = 0;
    int sum_even = 0;
    int total_sum = 0;
    int digit_count = 0;
    //for fck sake to check
    long cpy_num = card_num; 

    while (card_num > 0)
    {
        int current_digit = card_num % 10; //last digit

        if (digit_count % 2 == 0) //if odd
        {
            sum_odd += current_digit;
        }
        else
        {
            int double_digit = current_digit * 2; // double it
            if (double_digit > 9)
            {
                double_digit = (double_digit % 10) + 1; //add 2 digit num
            }
            sum_even += double_digit;
        }
        card_num /= 10;
        digit_count++;
    }
    total_sum = sum_odd + sum_even;
    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    if (digit_count == 15 && (cpy_num / 10000000000000 == 34 || cpy_num / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (digit_count == 16 && (cpy_num / 100000000000000 >= 51 && cpy_num / 100000000000000 <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digit_count == 13 || digit_count == 16) && (cpy_num / 1000000000000 == 4 || cpy_num / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}