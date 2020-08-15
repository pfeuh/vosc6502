
#include <stdio.h>
#include "emulator.h"
#include "memory.h"
#include "desass6502.h"
#include "fake6502.h"

byte read6502(word address)
{
    return memGet(address);
}

void write6502(word address, byte value)
{
    memPut(address, value);
}

void printRegisters()
{
    printf("PC:%04X SP:%02X A:%02X X:%02X Y:%02X S:", pc, sp, a, x, y);
    if(status & 128)
        printf("N");
    else
        printf(".");
    if(status & 64)
        printf("V");
    else
        printf(".");
    if(status & 32)
        printf("U");
    else
        printf(".");
    if(status & 16)
        printf("B");
    else
        printf(".");
    if(status & 8)
        printf("D");
    else
        printf(".");
    if(status & 4)
        printf("I");
    else
        printf(".");
    if(status & 2)
        printf("Z");
    else
        printf(".");
    if(status & 1)
        printf("C _ ");
    else
        printf(". _ ");
    desassOneLine(pc);
}

void setPC(word addr)
{
    pc = addr;
}

word getPC()
{
    return pc;
}

void setSP(byte value)
{
    sp = value;
}

byte getSP()
{
    return sp;
}
void setA(byte value)
{
    a = value;
}

void setX(byte value)
{
    x = value;
}

void setY(byte value)
{
    y = value;
}

void setStatus(byte value)
{
    status = value;
}

byte getStatus()
{
    return status;
}

void clearbreak()
{
    status &= ~FLAG_BREAK;
}

void setbreak()
{
    status |= FLAG_BREAK;
}

void clearunused()
{
    status &= ~FLAG_CONSTANT;
}

void setunused()
{
    status |= FLAG_CONSTANT;
}

bool hasInterrupt()
{
    return ((FLAG_INTERRUPT & status) != 0);
}

bool hasBreak()
{
    return ((FLAG_BREAK & status) != 0);
}

void setinterrupt()
{
    status |= FLAG_INTERRUPT;
}

void setcarry()
{
    status |= FLAG_CARRY;
}

void clearcarry()
{
    status &= (~FLAG_CARRY);
}

void setzero()
{
    status |= FLAG_ZERO;
}

void clearzero()
{
    status &= (~FLAG_ZERO);
}

void clearinterrupt()
{
    status &= (~FLAG_INTERRUPT);
}

void setdecimal()
{
    status |= FLAG_DECIMAL;
}

void cleardecimal()
{
    status &= (~FLAG_DECIMAL);
}

void setoverflow()
{
    status |= FLAG_OVERFLOW;
}

void clearoverflow()
{
    status &= (~FLAG_OVERFLOW);
}

void setsign()
{
    status |= FLAG_SIGN;
}

void clearsign()
{
    status &= (~FLAG_SIGN);
}

dword getTicks()
{
    return clockticks6502;
}

void setTicks(dword value)
{
    clockticks6502 = value;
}
