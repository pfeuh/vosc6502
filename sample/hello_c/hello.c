    
#include <peekpoke.h>

#define VOSC_IO_PUTSCR 0xbf00

const char hello_text[] = "Hello, World... But in C language!\n";

void writeln(char* text)
{
    while(*text)
        POKE(VOSC_IO_PUTSCR, *text++);
    POKE(VOSC_IO_PUTSCR, '\n');
}

int main()
{
    writeln((char*)hello_text);
    return 0;
}
