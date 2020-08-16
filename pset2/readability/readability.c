#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    string text = get_string("Text:");

    // get length of text
    int len = strlen(text);

    // initiatlize counters forletter, word, and sentence
    int letter_counter = 0;
    int word_counter = 1;
    int sentence_counter = 0;

    // loop over the total length of the text
    for (int i = 0; i < len; i++)
    {
        // detect if the current character is a letter
        if (isalpha(text[i]))
        {
            letter_counter += 1;
        }

        // if current character is a space, add one to word
        if (isspace(text[i]))
        {
            word_counter += 1;
        }

        // if a set of words end with a ".", "!" and "?", add one sentence
         else if ((text[i])== '.' || (text[i]) == '!' || (text[i]) == '?')
        {
           sentence_counter += 1;
        }
       
    }
    /*
    printf("%d letter(s)", letter_counter);
    printf("\n%d word(s)", word_counter);
    printf("\n%d sentence(s)", sentence_counter);*/

    // calculate the Coleman-Liau index
    float L = (float)letter_counter / (float)word_counter * 100.0f;
    float S = (float)sentence_counter / (float)word_counter * 100.0f;

    float index = 0.0588f * L - 0.296f * S - 15.8f;
    int trueIndex = (int)round(index);



    // Determine the grade levels using the index
    if (trueIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (trueIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", trueIndex);
    }

}
