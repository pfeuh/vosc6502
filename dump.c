
#include "dump.h"
#include "console.h"
#include <stdio.h>

char DUMP_scibuf[DUMP_NB_COLUMNS]; 

char DUMP_getAscii(char value)
{
    if(value < 32)
        return '.';
    else if(value < 128)
        return value;
    else
        return '.';
}

void dump(word addr, byte(*getbyte_hook)(word addr), word size)
{
    word counter = 0;
    byte octet;

    while(1)
    {
        if((counter % DUMP_NB_COLUMNS) == 0)
            printf("%04x ", addr);
        
        octet = getbyte_hook(addr);
        printf("%02x ", octet);
        DUMP_scibuf[counter % DUMP_NB_COLUMNS] = DUMP_getAscii(octet);
        DUMP_scibuf[(counter % DUMP_NB_COLUMNS) + 1] = CHAR_EOS;
        
        if((counter % DUMP_NB_COLUMNS) == (DUMP_NB_COLUMNS - 1))
            printf("%s\n", DUMP_scibuf);
        
        addr++;
        counter++;
        
        if(counter == size)
            break;
    }
    if((counter % DUMP_NB_COLUMNS) != 0)
    {
        while((counter++ % DUMP_NB_COLUMNS) != 0)
            printf("   ");
        printf("%s\n", DUMP_scibuf);
        
    }
}

