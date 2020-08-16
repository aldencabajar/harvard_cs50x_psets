#include <stdio.h>
#include <cs50.h>
int main(void)

{

    printf("hello world/n");

    // this will take a string as an input
    string name = get_string("What is your name?\n");

    // prints your name!
    printf("hello %s\n", name);
}