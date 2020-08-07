
#include "console.h"
#include "interpreter.h"
#include "main.h"
#include <string.h>

const char* ITP_errors[] = 
{
    "No error",                   // 0
    "Not enough parameter(s)",    // 1
    "Bad numeric input",          // 2
    "No table of commands found", // 3
    "Unknown command",            // 4
    "File not found",             // 5
    "Out of range input",         // 6
};

INTERPRETER_command* commandTable = NULL;

bool setupCommandTable(INTERPRETER_command* list_of_commands)
{
    commandTable = list_of_commands;
    return ITP_SUCCESS;
}

bool writeItpError(int error_num)
{
    printf("ERROR:%s!\n", ITP_errors[error_num]);
    return ITP_FAILURE;
}

bool execCommandline()
{
    char* cmd;
    int index = 0;
    bool ret_val;
    
    if(commandTable == NULL)
        return writeItpError(ITP_ERR_noCmdTable);
    
    cmd = getNextParameter();
    if(cmd == NULL)
        return ITP_FAILURE;
        
    while(commandTable[index].name != NULL)
    {
        if(!strcmp(commandTable[index].name, cmd))
        {
            ret_val = commandTable[index].hook();
            setMonitorContext();
            return ret_val;
        }
        index++;
    }
        
    return writeItpError(ITP_ERR_notFound);
}

bool execString(char* command)
{
    strcpy(commandlineBuf, command);
    if(verboseFlag)
        printf("%s\n", commandlineBuf);
    
    // don't need now but later for function getNextParameter()
    commandlineIndex = 0;    

    return execCommandline();
}

