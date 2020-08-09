#ifndef FAKE6502_H
#define FAKE6502_H

#define FLAG_CARRY     0x01
#define FLAG_ZERO      0x02
#define FLAG_INTERRUPT 0x04
#define FLAG_DECIMAL   0x08
#define FLAG_BREAK     0x10
#define FLAG_CONSTANT  0x20
#define FLAG_OVERFLOW  0x40
#define FLAG_SIGN      0x80

extern uint16_t pc;
extern uint8_t sp, a, x, y, status;
extern dword clockticks6502;

extern void reset6502();
extern void exec6502(uint32_t tickcount);
extern void step6502();
extern void irq6502();
extern void nmi6502();
extern void hookexternal(void *funcptr);
extern uint16_t getvalue16(void);

extern void clc();
extern void sec();
extern void cli();
extern void sei();
extern void clv();
extern void cld();
extern void sed();

#endif
