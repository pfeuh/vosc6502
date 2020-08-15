#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>

#define PUTCHAR_REG 0xef00

const char splash[] = "Hello, World!\n";

int putchar(int car)
{
    POKE(PUTCHAR_REG, car);
    return car;
}

void print(char* text)
{
    while(*text)
        putchar(*text++);
}

int main (void)
{
    print ((char*)splash);
    while(1);
    return EXIT_SUCCESS;
}
