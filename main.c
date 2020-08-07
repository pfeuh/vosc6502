
#include "console.h"
#include "interpreter.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
//~ #include <stdint.h>
#include <string.h>

#define VERSION "0.99"

#define PROMPT ">"

// TODO: BUG pc seems to follow desassGetNextByte()!
// TODO: BUG with io and unwired settings

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
#define VOSC_IO_INITRAND 0xbf80
#define VOSC_IO_GETRAND  0xbf80

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
    execString("wpoke fffa 123");
    execString("wpoke fffc 2004");
    execString("wpoke fffe 789");
    execString("poke be10 a9");
    execString("poke be11 a9");
    execString("poke be12 a9");
    execString("poke be13 a9");
    execString("poke ffe0 a9");
    
    memSetRom(0xc000, 0x4000);
    memSetUnwired(0xbf00, 0x100);
    memSetOutput(VOSC_IO_PUTSCR, putscr);
    memSetInput(VOSC_IO_GETKEY, getkey);    
    memSetOutput(VOSC_IO_INITRAND, initrand);
    memSetInput(VOSC_IO_GETRAND, getrand);  

    execString("reset");

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
    parseArguments(argc, argv);
    initHardware();
    
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
