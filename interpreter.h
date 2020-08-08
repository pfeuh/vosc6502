#ifndef INTERPRETER_H
#define INTERPRETER_H

#define ITP_SUCCESS false
#define ITP_FAILURE true

#define ITP_ERR_noError      0
#define ITP_ERR_notEnough    1
#define ITP_ERR_badNumeric   2
#define ITP_ERR_noCmdTable   3
#define ITP_ERR_notFound     4
#define ITP_ERR_fileNotFound 5
#define ITP_ERR_outOfRange   6
#define ITP_ERR_badCharacter 7

#include "types.h"

typedef bool (*INTERPRETER_HOOK)(void);

typedef struct
{
    char* name;
    INTERPRETER_HOOK hook;
}INTERPRETER_command;

extern bool setupCommandTable(INTERPRETER_command* list_of_commands);
extern bool execCommandline();
extern bool execString(char* command);
extern bool writeItpError(int error_num);

#endif