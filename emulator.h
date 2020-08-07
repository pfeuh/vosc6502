#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"
#include "fake6502.h"
#include "types.h"

extern void printRegisters();
extern void setPC(word addr);
extern void setSP(byte value);
extern void setA(byte value);
extern void setX(byte value);
extern void setY(byte value);
extern void setStatus(byte value);
extern byte getStatus();

extern void clearbreak();
extern void setbreak();
extern void clearunused();
extern void setunused();

extern bool hasInterrupt();
extern bool hasBreak();

#endif

