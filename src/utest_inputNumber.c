
#include "console.h"

int main(int argc, char* argv[])
{
    int value;
    bool flag;
    int base = 10;

    printf("select base:");
    feedCommandline();
    base = getNumber(10);
    if(!base)
        return 1;
    if(base > 16)
        return 2;
    
    while(1)
    {
        feedCommandline();
        value = getNumber(base);
        flag = isParameterOk();
        printf("%d --- base:%d --- result OK:%d\n", value, base, flag);
    }    
    
    return 0;
}