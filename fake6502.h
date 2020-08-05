#ifndef FAKE6502_H
#define FAKE6502_H

#include <stdint.h>

#define FLAG_CARRY     0x01
#define FLAG_ZERO      0x02
#define FLAG_INTERRUPT 0x04
#define FLAG_DECIMAL   0x08
#define FLAG_BREAK     0x10
#define FLAG_CONSTANT  0x20
#define FLAG_OVERFLOW  0x40
#define FLAG_SIGN      0x80

//flag modifier macros NV-BDIZC
#define setcarry() status |= FLAG_CARRY
#define clearcarry() status &= (~FLAG_CARRY)
#define setzero() status |= FLAG_ZERO
#define clearzero() status &= (~FLAG_ZERO)
#define setinterrupt() status |= FLAG_INTERRUPT
#define clearinterrupt() status &= (~FLAG_INTERRUPT)
#define setdecimal() status |= FLAG_DECIMAL
#define cleardecimal() status &= (~FLAG_DECIMAL)
#define setoverflow() status |= FLAG_OVERFLOW
#define clearoverflow() status &= (~FLAG_OVERFLOW)
#define setsign() status |= FLAG_SIGN
#define clearsign() status &= (~FLAG_SIGN)

extern uint16_t pc;
extern uint8_t sp, a, x, y, status;

extern void reset6502();
extern void exec6502(uint32_t tickcount);
extern void step6502();
extern void irq6502();
extern void nmi6502();
extern void hookexternal(void *funcptr);

extern void clc();
extern void sec();
extern void cli();
extern void sei();
extern void clv();
extern void cld();
extern void sed();

#endif
