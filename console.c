
#include <string.h>
#include "console.h"

char commandlineBuf[COMMANDLINE_BUF_SIZE];
char parameterBuf[COMMANDLINE_BUF_SIZE];
int  commandlineIndex;
bool parameterOkFlag;

void setMonitorContext()
{
    printf("%c[%sm", CHAR_ESCAPE, COLOR_DEFAULT);
}

void setEmulatorContext()
{
    printf("%c[%sm", CHAR_ESCAPE, COLOR_YELLOW);
}

void setBreakContext()
{
    printf("%c[%sm", CHAR_ESCAPE, COLOR_BOLD_GREEN);
}

bool isParameterOk()
{
    return parameterOkFlag;
}

char* getNextParameter()
{
    bool end_of_argument = false;
    int param_index = 0;
    char car;
    
    parameterOkFlag = true;
    
    // ignoring garbage spaces
    while(commandlineBuf[commandlineIndex] == CHAR_SPACE)
        commandlineIndex++;

    // no mode characters => no more parameter
    if(commandlineBuf[commandlineIndex] == CHAR_EOS)
    {
        parameterOkFlag = false;
        return NULL;
    }
    
    while(!end_of_argument)
    {
        car = commandlineBuf[commandlineIndex];
        switch(car)
        {
            case CHAR_SPACE:
                parameterBuf[param_index] = CHAR_EOS;
                end_of_argument = true;
                commandlineIndex++;
                break;
            case CHAR_SEMICOLON:
            case CHAR_EOS:
                parameterBuf[param_index] = CHAR_EOS;
                end_of_argument = true;
                break;
            default:
                commandlineIndex++;
                parameterBuf[param_index++] = car;
                parameterBuf[param_index] = CHAR_EOS;
                break;
        }
    }
    if(parameterBuf[0] == CHAR_EOS)
        return NULL;
    else
        return parameterBuf;
}

unsigned int getHexNumber()
{
    char* input_ptr = getNextParameter();
    unsigned int uint_value = 0;
    char car;
    
    if(input_ptr == NULL)
    {
        parameterOkFlag = false;
        return 0;
    }
    
    parameterOkFlag = true;

    if(input_ptr == NULL)
        parameterOkFlag = false;
    
    while(*input_ptr)
    {
        car = *input_ptr++;
        switch(car)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                uint_value = uint_value * 16 + car - '0';
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                uint_value = uint_value * 16 + car + 10 - 'a';
                break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                uint_value = uint_value * 16 + car + 10 - 'A';
                break;
            default:
                parameterOkFlag = false;
                break;
        }
    }
    return uint_value;
}

bool feedCommandline()
{
    int car;
    
    commandlineIndex = 0;
    commandlineBuf[commandlineIndex] = 0;
    
    while(1)
    {
        car = getc(stdin);
        if(car == '\n')
            break;
        commandlineBuf[commandlineIndex++] = car;
        commandlineBuf[commandlineIndex] = 0;
    }
    if(commandlineIndex == 0)
        return CONSOLE_FAILURE;
    
    // don't need now but later for function getNextParameter()
    commandlineIndex = 0;
    
    return CONSOLE_SUCCESS;
}

bool copyCommandline(char* command)
{
    strcpy(commandlineBuf, command);

    // don't need now but later for function getNextParameter()
    commandlineIndex = 0;    

    return CONSOLE_SUCCESS;
}
