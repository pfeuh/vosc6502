
#include <string.h>
#include "interpreter.h"
#include "console.h"
#include "memory.h"
#include "commands.h"
#include "dump.h"
#include "desass6502.h"
#include "emulator.h"
#include "finder.h"
#include "main.h"

char batBuffer[COMMANDLINE_BUF_SIZE];
byte finderPattern[FINDER_PATTERN_SIZE];
word finderPatternSize;
word finderPatternIndex;

void enterEmulation()
{
    setEmulatorContext();
}

void exitEmulation()
{
    if(hasBreak())
        setBreakContext();

    else if(hasInterrupt())
        setInterruptContext();

    else
        setMonitorContext();

    printRegisters();
}


void displayVerboseFlag()
{
    if(verboseFlag)
        printf("verbose flag is ON\n");
    else
        printf("verbose flag is OFF\n");
}

/*****************/
/* 6502 commands */
/*****************/

bool cmdRun()
{
    word value;
    
    value  = getHexNumber();
    if(!isParameterOk());
        // whithout parameter, program counter (run address) is not modified
    else
        pc = value;
    
    enterEmulation();
    while(1)
    {
        step6502();
        if(memIsBreak(pc))
            break;
    }
    exitEmulation();
    
    return ITP_SUCCESS;
}

bool cmdStep()
{
    word value;
    
    value  = getHexNumber();
    if(!isParameterOk());
        // whithout parameter, program counter (run address) is not modified
    else
        pc = value;
    
    enterEmulation();
    step6502();
    exitEmulation();
    
    return ITP_SUCCESS;
}

bool cmdPrintRegisters()
{
    printRegisters();
    return ITP_SUCCESS;
}


bool cmdSetPC()
{
    word addr;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    setPC(addr);
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSetSP()
{
    byte value;
    
    value  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    setSP(value);
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSetA()
{
    byte value;
    
    value  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    setA(value);
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSetX()
{
    byte value;
    
    value  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    setX(value);
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSetY()
{
    byte value;
    
    value  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    setY(value);
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdStatus()
{
    byte value;
    
    value  = getHexNumber();
    if(!isParameterOk());
        // whithout parameter status is not modified
    else
        setStatus(value);
    printf("%02x\n", status);
    return ITP_SUCCESS;
}

bool cmdClc()
{
    clearcarry();
    printRegisters();

    return ITP_SUCCESS;
}

bool cmdSec()
{
    setcarry();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdCli()
{
    clearinterrupt();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSei()
{
    setinterrupt();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSev()
{
    setoverflow();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdClv()
{
    clearoverflow();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdCld()
{
    cleardecimal();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSed()
{
    setdecimal();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdClz()
{
    clearzero();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSez()
{
    setzero();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdClb()
{
    clearbreak();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSeb()
{
    setbreak();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdCls()
{
    clearsign();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSes()
{
    setsign();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdClu()
{
    clearunused();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdSeu()
{
    setunused();
    printRegisters();
    
    return ITP_SUCCESS;
}

bool cmdReset()
{
    reset6502();
    printRegisters();
    
    return ITP_SUCCESS;
}

/************************/
/* end of 6502 commands */
/************************/

word dessasStackPointer;

// this function has to be provided to desass6502
word desassGetAddr()
{
    return dessasStackPointer;
}

// this function has to be provided to desass6502
void desassSetAddr(word addr)
{
    dessasStackPointer = addr;
}

// this function has to be provided to desass6502
byte desassGetNextByte()
{
    return memGet(dessasStackPointer++);
}

void bat(char* fname)
{
    FILE *fp;
    int read_size = 1;
    int eof;
    char dummy;
    
    fp = fopen(fname, "rb");
    if (fp == NULL) 
    {
        writeItpError(ITP_ERR_fileNotFound);
		return;
    }
    
    clearerr(fp); 
    eof = feof(fp);
    while(!eof)
    {
        read_size = fscanf(fp, "%[^\n]", batBuffer);
        if(read_size < 0)
            break;
        eof = feof(fp);
        if(read_size == 1)
        {
            printf("%s\n", batBuffer);
            copyCommandline(batBuffer);
            execCommandline();
        }
        // must go manually to the next input byte, I don't know why...
        //~ fseek(fp, 1, SEEK_CUR);
        read_size = fread(&dummy, sizeof(char), 1, fp);
    }
	fclose(fp);
}

/********************/
/* MONITOR COMMANDS */
/********************/

bool cmdMemMap()
{
    memMap();
    return ITP_SUCCESS;
}

bool cmdMemHmap()
{
    memHmap();
    return ITP_SUCCESS;
}

bool cmdSetBreak()
{
    word addr;
    bool value;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    value = getHexNumber();
    // let the second parameter be optional
    if(!isParameterOk())
        value = true;
    
    memSetBreak(addr, value);
    return ITP_SUCCESS;
}

bool cmdVerboseFlag()
{
    bool value;
    
    value = getHexNumber();
    // let the parameter be optional
    if(isParameterOk())
    {
        if(value)
            verboseFlag = true;
        else
            verboseFlag = false;
    }
    displayVerboseFlag();
    return ITP_SUCCESS;
}

bool cmdListBreaks()
{
    memListBreaks();
    return ITP_SUCCESS;
}

bool cmdClrBreaks()
{
    memClrBreaks();
    return ITP_SUCCESS;
}

bool cmdDump()
{
    word addr;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    dump(addr, memGet);
    return ITP_SUCCESS;
}

bool cmdPeek()
{
    word addr;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    printf("%02x\n", memGet(addr));
    return ITP_SUCCESS;
}

bool cmdWpeek()
{
    word addr;
    word value;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    value = memGet(addr) + 256 * memGet(addr + 1);
    
    printf("%04x\n", memGet(value));
    return ITP_SUCCESS;
}

bool cmdPoke()
{
    word addr;
    byte value;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    value  = getHexNumber(); 
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    memPut(addr++, value);

    // extra parameters
    while(1)
    {
        value  = getHexNumber(); 
        if(!isParameterOk())
            return ITP_SUCCESS;

        memPut(addr++, value);
    }
    
    return ITP_SUCCESS;
}

bool cmdWpoke()
{
    word addr;
    word value;
    
    addr  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    value  = getHexNumber(); 
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);

    memPut(addr++, value & 255);
    memPut(addr++, value / 256);

    // extra parameters
    while(1)
    {
        value  = getHexNumber(); 
        if(!isParameterOk())
            return ITP_SUCCESS;

        memPut(addr++, value & 255);
        memPut(addr++, value / 256);
    }
    
    return ITP_SUCCESS;
}

bool cmdDesass()
{
    word addr;
    word nb_lines;
    
    addr  = getHexNumber();
    if(!isParameterOk())
    {
        // OK to ommit first parameter
        addr = pc;
        nb_lines = 10;
    }
    else
    {
        nb_lines  = getHexNumber(); 
        if(!isParameterOk())
            // OK to ommit second parameter
            nb_lines = 10;
    }
    
    desass(addr,nb_lines);

    return ITP_SUCCESS;
}

bool cmdLoadFile()
{
    char* temp_ptr;
    char fname[COMMANDLINE_BUF_SIZE];
    word addr;
    word size;
    
    
    temp_ptr  = getNextParameter(); 
    if(!isParameterOk())
        return writeItpError(ITP_ERR_notEnough);

    strcpy(fname, temp_ptr);
    
    addr = getHexNumber();
    // OK to ommit second parameter
    if(!isParameterOk())
        addr = 0;
    
    size = memLoadFile(fname, addr);
    if(!size)
        return writeItpError(ITP_ERR_fileNotFound);
    printf("%d bytes loaded\n", size);    
    return ITP_SUCCESS;
}

bool cmdBat()
{
    char* temp_ptr;
    char fname[COMMANDLINE_BUF_SIZE];
    
    temp_ptr  = getNextParameter(); 
    if(!isParameterOk())
        return writeItpError(ITP_ERR_notEnough);

    strcpy(fname, temp_ptr);
    
    bat(fname);
    return ITP_SUCCESS;
}

bool cmdFind()
{
    byte value;
    
    finderPatternSize = 0;

    value  = getHexNumber();
    if(!isParameterOk())
        return writeItpError(ITP_ERR_badNumeric);
    
    finderPattern[finderPatternSize++] = value;
    //~ printf("Searching for %02X", value);
    
    while (1)
    {
        value  = getHexNumber();
        if(!isParameterOk())
            break;
        finderPattern[finderPatternSize++] = value;
        //~ printf(" %02X", value);
    }
    //~ printf("...\n");
    
    find(finderPattern, finderPatternSize);
    
    return ITP_SUCCESS;
}

bool cmdLoadAtariFile()
{
    word size;
    char* fname;
    
    fname = getNextParameter(); 
    if(!isParameterOk())
        return writeItpError(ITP_ERR_notEnough);

    size = memLoadAtariFile(fname);
    
    if(!size)
        return writeItpError(ITP_ERR_fileNotFound);
    printf("%d bytes loaded\n", size);
    return ITP_SUCCESS;
}

bool cmdQuitApp()
{
    exit(0);
    return ITP_FAILURE;
}

INTERPRETER_command listOfCommands[] =
{
    {"exit", cmdQuitApp},          // quit application
    {"bye", cmdQuitApp},           // quit application
    {"peek", cmdPeek},             // display a byte of memory
    {"wpeek", cmdWpeek},           // display a word of memory
    {"poke", cmdPoke},             // set a byte of memory
    {"wpoke", cmdWpoke},           // set a word of memory
    {"d", cmdDump},             // display a piece of memory
    {"load", cmdLoadFile},         // put a binary file in memory 
    {"ataload", cmdLoadAtariFile}, // put an Atari binary file in memory 
    {"sb", cmdSetBreak},           // set/clear a breakpoint
    {"lb", cmdListBreaks},         // list all breakpoints
    {"cb", cmdClrBreaks},          // clear all breakpoints
    {"hmap", cmdMemHmap},          // mapping of hardware
    {"map", cmdMemMap},            // mapping of used ram
    {"u", cmdDesass},              // unassemble a piece of memory
    {"bat", cmdBat},               // execute a batch file
    {"vf", cmdVerboseFlag},        // display set or clear verbose flag
    {"f", cmdFind},                // find a pattern in memory

// 6502 emulator specific instructions
    
    {"regs", cmdPrintRegisters},   // print 6502 registers
    {"reset", cmdReset},           // reset 6502
    {"regs", cmdPrintRegisters},   // print 6502 registers
    {"pc", cmdSetPC},              // set 6502 program counter
    {"sp", cmdSetSP},              // set 6502 stack pointer
    {"a", cmdSetA},                // set 6502 accumulator
    {"x", cmdSetX},                // set 6502 X register
    {"status", cmdStatus},         // display or write 6502 Y register
    {"y", cmdSetY},                // set 6502 Y register
    {"clc", cmdClc},               // 6502 instruction's "clc"
    {"sec", cmdSec},               // 6502 instruction's "sec"
    {"cli", cmdCli},               // 6502 instruction's "cli"
    {"sei", cmdSei},               // 6502 instruction's "sei"
    {"sev", cmdSev},               // set overflow flag (doesn' exist in 6502)
    {"clv", cmdClv},               // 6502 instruction's "clv"
    {"cld", cmdCld},               // 6502 instruction's "cld"
    {"sed", cmdSed},               // 6502 instruction's "sed"
    {"clz", cmdClz},               // clear zero flag (doesn' exist in 6502)
    {"sez", cmdSez},               // set zero flag (doesn' exist in 6502)
    {"clb", cmdClb},               // clear break flag (doesn' exist in 6502)
    {"seb", cmdSeb},               // set break flag (doesn' exist in 6502)
    {"cls", cmdCls},               // clear sign flag (doesn' exist in 6502)
    {"ses", cmdSes},               // set sign flag (doesn' exist in 6502)
    {"clu", cmdClu},               // clear unused flag (doesn' exist in 6502)
    {"seu", cmdSeu},               // set unused flag (doesn' exist in 6502)
    {"s", cmdStep},                // 6502 executes 1 instruction
    {"r", cmdRun},                 // 6502 executes without end
    
    {NULL, NULL}                   // end of commands' table 
};

