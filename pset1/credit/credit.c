#include <stdio.h>
#include <cs50.h>
#include <math.h>



int main(void)
{

    long digits = get_long("Number:");

    //check if the length of the digit input is correct
    int i = 0;
    long digits_ = digits;
    while (digits_ != 0)
    {
        digits_ /= 10;
        i += 1;
    }


    // if the digit length is not equal to 13,15 and 16, throw out an error
    if (i != 15 & i != 13 & i != 16)
    {
        printf("INVALID\n");
    }

    else

    {

        // store the first and second numbers
        int num1 = digits / pow(10, i - 1);
        int num2 = (int)(digits / pow(10, i - 2)) % 10;

        // initialize sums of digits from the end (sum_end) and from the second last (sum_skip)
        int sum_skip = 0;
        int sum_end = 0;
        int j = 1;

        while (digits != 0)
        {

            if ((j % 2) == 0)
            {
                int prod = (digits % 10) * 2;
                // this loop "unfolds" products with more than two digits
                while (prod != 0)
                {
                    sum_skip += prod % 10;
                    prod /= 10;
                }

            }
            else
            {
                sum_end += digits % 10;
            }

            digits /= 10;

            j += 1;

        }


        int sum_all = sum_skip + sum_end;

        int mod = sum_all % 10;


        // detects now if the card number is invalid or one of the different types of cards
        if (mod != 0)
        {
            printf("INVALID\n");
        }
        else

        {

            if (num1 == 5 & num2 <= 5 & num2 > 0)
            {
                printf("MASTERCARD\n");

            }
            else if ((num1 == 3) & (num2 == 4 | num2 == 7))
            {

                printf("AMEX\n");

            }
            else if (num1 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                //for everything else, set it to INVALID
                printf("INVALID\n");
            }

        }




    }
}