#ifndef DESASS_6502_TABLES_H
#define DESASS_6502_TABLES_H

/****************************/
/* VERSION 1.0 - 19/08/2020 */
/****************************/

extern void Immediate();
extern void Implied ();
extern void Accumulator();
extern void ZeroPage();
extern void ZeroPageX();
extern void ZeroPageY();
extern void IndirectX();
extern void IndirectY();
extern void Absolute();
extern void AbsoluteX();
extern void AbsoluteY();
extern void Indirect();
extern void Relative();

const char* mnemo[] =
{
    "brk","ora","???","???","???","ora","asl","???","php","ora","asl","???","???","ora","asl","???", // 0x00 
    "bpl","ora","???","???","???","ora","asl","???","clc","ora","???","???","???","ora","asl","???", // 0x10 
    "jsr","and","???","???","bit","and","rol","???","plp","and","rol","???","bit","and","rol","???", // 0x20 
    "bmi","and","???","???","???","and","rol","???","sec","and","???","???","???","ora","asl","???", // 0x30 
    "rti","eor","???","???","???","eor","lsr","???","pha","eor","lsr","???","jmp","eor","lsr","???", // 0x40 
    "bvc","eor","???","???","???","eor","lsr","???","cli","eor","???","???","???","eor","lsr","???", // 0x50 
    "rts","adc","???","???","???","adc","ror","???","pla","adc","ror","???","jmp","adc","ror","???", // 0x60 
    "bcs","adc","???","???","???","adc","ror","???","sei","adc","???","???","???","adc","ror","???", // 0x70 
    "???","sta","???","???","sty","sta","stx","???","dey","???","txa","???","sty","sta","stx","???", // 0x80 
    "bcc","sta","???","???","sty","sta","stx","???","tya","sta","txs","???","???","sta","???","???", // 0x90 
    "ldy","lda","ldx","???","ldy","lda","ldx","???","tay","lda","tax","???","ldy","lda","ldx","???", // 0xa0 
    "bcs","lda","???","???","ldy","lda","ldx","???","clv","lda","tsx","???","ldy","lda","ldx","???", // 0xb0 
    "cpy","cmp","???","???","cpy","cmp","dec","???","iny","cmp","dex","???","cpy","cmp","dec","???", // 0xc0 
    "bne","cmp","???","???","???","cmp","dec","???","cld","cmp","???","???","???","cmp","dec","???", // 0xd0 
    "cpx","sbc","???","???","cpx","sbc","inc","???","inx","sbc","nop","???","cpx","sbc","inc","???", // 0xe0 
    "beq","sbc","???","???","???","sbc","inc","???","sed","sbc","???","???","???","sbc","inc","???"  // 0xf0 
};

void(*hook[])(void) = 
{
    Implied ,   IndirectX,   Implied ,  Implied ,   Implied ,   ZeroPage,   ZeroPage,   Implied , // 0x00
    Implied ,   Immediate,  Accumulator,Implied ,   Implied ,   Absolute,   Absolute,   Implied , // 0x08
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0x10
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied , // 0x18
    Absolute,   IndirectX,  Implied ,   Implied ,   ZeroPage,   ZeroPage,   ZeroPage,   Implied , // 0x20
    Implied ,   Immediate,  Accumulator,Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0x28
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0x30
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied , // 0x38
    Implied ,   IndirectX,  Implied ,   Implied ,   Implied ,   ZeroPage,   ZeroPage,   Implied , // 0x40
    Implied ,   Immediate,  Accumulator,Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0x48
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0x50
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied , // 0x58
    Implied ,   IndirectX,  Implied ,   Implied ,   Implied ,   ZeroPage,   ZeroPage,   Implied , // 0x60
    Implied ,   Immediate,  Accumulator,Implied ,   Indirect,   Absolute,   Absolute,   Implied , // 0x68
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0x70
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied , // 0x78
    Implied ,   IndirectX,  Implied ,   Implied ,   ZeroPage,   ZeroPage,   ZeroPage,   Implied , // 0x80
    Implied ,   Implied ,   Implied ,   Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0x88
    Relative,   IndirectY,  Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  ZeroPageY,  Implied , // 0x90
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  Implied ,   Implied , // 0x98
    Immediate,  IndirectX,  Immediate,  Implied ,   ZeroPage,   ZeroPage,   ZeroPage,   Implied , // 0xa0
    Implied ,   Immediate,  Implied ,   Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0xa8
    Relative,   IndirectY,  Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  ZeroPageY,  Implied , // 0xb0
    Implied ,   AbsoluteY,  Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  AbsoluteY,  Implied , // 0xb8
    Immediate,  IndirectX,  Implied ,   Implied ,   ZeroPage,   ZeroPage,   ZeroPage,   Implied , // 0xc0
    Implied ,   Immediate,  Implied ,   Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0xc8
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0xd0
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied , // 0xd8
    Immediate,  IndirectX,  Implied ,   Implied ,   ZeroPage,   ZeroPage,   ZeroPage,   Implied , // 0xe0
    Implied ,   Immediate,  Implied ,   Implied ,   Absolute,   Absolute,   Absolute,   Implied , // 0xe8
    Relative,   IndirectY,  Implied ,   Implied ,   Implied ,   ZeroPageX,  ZeroPageX,  Implied , // 0xf0
    Implied ,   AbsoluteY,  Implied ,   Implied ,   Implied ,   AbsoluteX,  AbsoluteX,  Implied   // 0xf8
};

#endif
