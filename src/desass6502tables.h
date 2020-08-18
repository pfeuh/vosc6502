#ifndef DESASS_6502_TABLES_H
#define DESASS_6502_TABLES_H

/****************************/
/* VERSION 1.0 - 19/08/2020 */
/****************************/

extern void immediate();
extern void inherent();
extern void accumulator();
extern void zeropage();
extern void zeropagex();
extern void zeropagey();
extern void indzerox();
extern void indzeroy();
extern void absolute();
extern void absolx();
extern void absoly();
extern void indirect();
extern void relative();

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
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent, // 0x00
    inherent,   immediate,  accumulator,inherent,   inherent,   absolute,   absolute,   inherent, // 0x08
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0x10
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent, // 0x18
    absolute,   indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent, // 0x20
    inherent,   immediate,  accumulator,inherent,   absolute,   absolute,   absolute,   inherent, // 0x28
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0x30
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent, // 0x38
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent, // 0x40
    inherent,   immediate,  accumulator,inherent,   absolute,   absolute,   absolute,   inherent, // 0x48
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0x50
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent, // 0x58
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent, // 0x60
    inherent,   immediate,  accumulator,inherent,   indirect,   absolute,   absolute,   inherent, // 0x68
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0x70
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent, // 0x78
    inherent,   indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent, // 0x80
    inherent,   inherent,   inherent,   inherent,   absolute,   absolute,   absolute,   inherent, // 0x88
    relative,   indzeroy,   inherent,   inherent,   zeropagex,  zeropagex,  zeropagey,  inherent, // 0x90
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     inherent,   inherent, // 0x98
    immediate,  indzerox,   immediate,  inherent,   zeropage,   zeropage,   zeropage,   inherent, // 0xa0
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent, // 0xa8
    relative,   indzeroy,   inherent,   inherent,   zeropagex,  zeropagex,  zeropagey,  inherent, // 0xb0
    inherent,   absoly,     inherent,   inherent,   absolx,     absolx,     absoly,     inherent, // 0xb8
    immediate,  indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent, // 0xc0
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent, // 0xc8
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0xd0
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent, // 0xd8
    immediate,  indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent, // 0xe0
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent, // 0xe8
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent, // 0xf0
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent  // 0xf8
};

#endif
