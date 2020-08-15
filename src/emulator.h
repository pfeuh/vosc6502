#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"

extern void printRegisters();
extern void setPC(word addr);
extern word getPC();
extern void setSP(byte value);
extern byte getSP();
extern void setA(byte value);
extern void setX(byte value);
extern void setY(byte value);
extern void setStatus(byte value);
extern byte getStatus();
extern dword getTicks();
extern void setTicks(dword value);


extern bool hasInterrupt();
extern bool hasBreak();

extern void reset6502();
extern void nmi6502();
extern void irq6502();
extern void exec6502(dword tickcount);
extern void step6502();
extern void hookexternal(void *funcptr);

extern void setinterrupt();
extern void setcarry();
extern void clearcarry();
extern void setzero();
extern void clearzero();
extern void setinterrupt();
extern void clearinterrupt();
extern void setdecimal();
extern void cleardecimal();
extern void setoverflow();
extern void clearoverflow();
extern void setsign();
extern void clearsign();
// doesnt exist in 6502 but useful for debugging
extern void clearbreak();
extern void setbreak();
extern void clearunused();
extern void setunused();

#endif

