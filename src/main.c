
#include "console.h"
#include "interpreter.h"
#include "commands.h"
#include "emulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.99"

#define PROMPT ">"

// TODO: BUG with io and unwired settings
// TODO: finish timer(s) module
// TODO: fix  warning: 'getvalue16' defined but not used [-Wunused-function]
// TODO: implement command over() for jump over a jsr in step by step mode
// TODO: check command cmdStack a little bit

// TODO: HARDWARE
// TODO: Real time clock
// TODO: UART
// TODO: joystick

// HARDWARE
#include "memory.h"

#include "screen.h"
#define VOSC_IO_PUTSCR 0xbf00

#include "keyboard.h"
#define VOSC_IO_GETKEY 0xbf00

#include "random.h"
#define VOSC_IO_INITRAND 0xef80
#define VOSC_IO_GETRAND  0xef80

bool autoRun = false;
bool verboseFlag = false;
bool appStartFlag = true;

void splashScreen()
{
    printf("VOSC6502 (Virtual Old School Computer with a 6502 processor)\n");
    printf("version %s -------------------------- MMXX - Pierre Faller\n\n", VERSION);
}

void initHardware()
{
    // HARDWARE COLD RESET
    
    // disconnect all
    memSetUnwired(0, 0x10000);
    
    // add some RAM
    memSetRam(0x0, 0xef00);
    
    // add some ROM
    memSetRom(0xf000, 0x1000);
    
    // add some ios
    memSetOutput(VOSC_IO_PUTSCR, putscr);
    memSetInput(VOSC_IO_GETKEY, getkey);    
    memSetOutput(VOSC_IO_INITRAND, initrand);
    memSetInput(VOSC_IO_GETRAND, getrand);  
    
    // clear all break points
    memClrBreaks();
    
    // reset the 6502
    reset6502();
}

int parseArguments(int argc, char* argv[])
{
    int idx = 0;
    
    while(idx < argc)
    {
        if(!strcmp(argv[idx], "-bat"))
        {
            idx++;
            if(idx >= argc)
                return EXIT_FAILURE;
            bat(argv[idx]);
        }
        if(!strcmp(argv[idx], "-run"))
            autoRun = true;
        if(!strcmp(argv[idx], "-verbose"))
            verboseFlag = true;
        idx++;
    }
    
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    setMonitorContext();
    splashScreen();
    setupCommandTable(listOfCommands);
    initHardware();

    parseArguments(argc, argv);
    
    appStartFlag = false;
    execString("regs");
    if(autoRun)
        execString("r");

    // MAIN SEQUENCER
    while(1)
    {
        printf(PROMPT);
        if(feedCommandline() == CONSOLE_SUCCESS)
            execCommandline();
    }
    return EXIT_SUCCESS;
}
