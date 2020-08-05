
#include "finder.h"
#include <stdio.h>

word finderPatternIndex;

void find(byte* pattern, word pattern_size)
{
    int addr = 0;
    bool found;
    word index;
    
    printf("<");
    for(index = 0; index < pattern_size; index++)
        printf("%02X ", pattern[index]);
    printf(">\n");
    
    while(addr < (MEMORY_SIZE - pattern_size + 1))
    {
        //~ printf("%04x ", addr);
        found = true;
        for(index = 0; index < pattern_size; index++)
        {
            if(!memIsStorage(addr + index))
            {
                // no need to search on i/o or unwired areas
                found = false;
                break;
            }
            if(memGet(addr + index) != pattern[index])
            {
                // if even one byte is different, no need to finish this step
                found = false;
                break;
            }
        }
        if(found)
            printf("%04X ", addr);
        addr++;
    }
}

