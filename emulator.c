
#include <stdio.h>
//~ #include "fake6502.h"
//~ #include "types.h"
#include "emulator.h"
#include "memory.h"
#include "desass6502.h"

uint8_t read6502(uint16_t address)
{
    return memGet(address);
}

void write6502(uint16_t address, uint8_t value)
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
    desass(pc, 1);
}

void setPC(word addr)
{
    pc = addr;
}

void setSP(byte value)
{
    sp = value;
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

