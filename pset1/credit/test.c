#include <stdio.h>


int main(void)

{
    long n = 4003600000000014;
    while(n != 0) {
        printf("%li", n % 10);
        n /= 10;
    }

}