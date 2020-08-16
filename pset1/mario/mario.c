#include <stdio.h>
#include <cs50.h>

int main(void)

{
    // get height from user input
    int height = 0;

    while ((height <= 0) || (height > 8))
    {
        height = get_int("Height:");

    }
    /* declare variables for clarity, this includes the boundary
    of the first hashes, and the total length that includes the two spaces and a
    newline character
    */
    int bound = height + 2;
    int total_length = 2 * height + 2;

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= total_length; j++)
        {
            // spaces before the first start of hashes, depending on the height
            if (j <= height - i)
            {
                printf(" ");
            }

            //hashes between height and start of hash
            else if ((j > height - i) & (j <= height))
            {
                printf("#");
            }
            // spaces between the height and the length of two spaces
            else if ((j > height) & (j <= bound))
            {
                printf(" ");
            }
            // hashes after bound + height hash length
            else if ((j > bound) & (j <= bound + i))
            {
                printf("#");
            }
            // spaces after the bound + height hash length
            else if ((j > bound + i) & (j < total_length))
            {
                printf("");
            }
            //new line character
            if (j == total_length)

            {
                printf("\n");
            }


        }
    }


}

