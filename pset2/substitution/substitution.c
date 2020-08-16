#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


bool check_dup(char c, string key);

int main(int argc, string argv[])
{
    int ni = 0;
    //detect if the length of arguments is correct
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // detect the length of the string input (should be equal to 26)
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            ni++;

            // exit if it is not a letter
            if (!isalpha(argv[1][i]))
            {
                return 1;
            }
            else if (check_dup(argv[1][i], argv[1]))
            {
                return 1;
            }
        }

        if (ni != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    //get string input from user
    string ptxt = get_string("plaintext: ");

    // normalize to all uppercase, get the difference between alphabet
    // and the key
    int key_upr[strlen(argv[1])];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        key_upr[i] = toupper(argv[1][i]);

    }

    // encrypt the plaintext using the key
    //create two arrays, one for knowing if there is a need to revert back to the original case,
    // the other one for the cipher
    int len_ptxt = strlen(ptxt);
    int ciph[len_ptxt];

    printf("ciphertext: ");
    for (int i = 0; i < len_ptxt; i++)
    {
        if (isalpha(ptxt[i]))
        {
            int rev = (int)ptxt[i] - toupper(ptxt[i]);
            //detect the appropriate index from the key
            int k = toupper(ptxt[i]) - 65; //65 is the ascii code for A
            ciph[i] = rev + key_upr[k];

        }
        // retain the character if it is not a letter
        else
        {
            ciph[i] = (int)ptxt[i];
        }

        printf("%c", ciph[i]);



    }
    printf("\n");


}

// functions checks if there are duplicate keys
bool check_dup(char c, string key)
{
    bool dup = false;
    int k = 0;
    // for each letter in the key, check if there are
    // repetitions
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] == c)
        {
            k++;
        }
    }
    // k should not exceed 1. if it is equal to 1,
    // it means that there is only 1 such letter.
    if (k > 1)
    {
        dup = true;
    }

    return dup;

}


