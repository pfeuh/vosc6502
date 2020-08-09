
#include "screen.h"
#include <stdio.h>

//~ const char screen_dummy[] = "Virtual input simulation\n";

byte getkey(void)
{
    return getchar();
    //~ static int index = 0;
    
    //~ byte value = screen_dummy[index++];
    
    //~ if(value == 0)
    //~ {
        //~ index = 0;
        //~ value = screen_dummy[index++];
    //~ }
    
    //~ return value;

}

