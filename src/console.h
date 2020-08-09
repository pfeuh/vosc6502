#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define CONSOLE_SUCCESS false
#define CONSOLE_FAILURE true

#define CHAR_EOS 0
#define CHAR_SPACE ' '
#define CHAR_ESCAPE 0x1b
#define CHAR_SEMICOLON ';'

#define COLOR_RED          "0;31"
#define COLOR_BOLD_RED     "1;31"
#define COLOR_GREEN        "0;32"
#define COLOR_BOLD_GREEN   "1;32"
#define COLOR_YELLOW       "0;33"
#define COLOR_BOLD_YELLOW  "1;33"
#define COLOR_BLUE         "0;34"
#define COLOR_BOLD_BLUE    "1;34"
#define COLOR_MAGENTA      "0;35"
#define COLOR_BOLD_MAGENTA "1;35"
#define COLOR_CYAN         "0;36"
#define COLOR_BOLD_CYAN    "1;36"
#define COLOR_DEFAULT      "0"

#define COMMANDLINE_SIZE 8192
#define COMMANDLINE_BUF_SIZE (COMMANDLINE_SIZE + 1)

extern char commandlineBuf[COMMANDLINE_BUF_SIZE];
extern int  commandlineIndex;

extern bool feedCommandline();
extern bool copyCommandline(char* command);
extern char* getNextParameter();
unsigned int getNumber(byte base);
extern unsigned int getHexNumber();

extern bool isParameterOk();
extern void setMonitorContext();
extern void setEmulatorContext();
extern void setBreakContext();
extern void setInterruptContext();

#endif

