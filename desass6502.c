
#include "desass6502.h"
#include <stdio.h>

enum displayMode SHOW_MODE = MODE_ASM;

// meno table is at the end of this file
extern const char* mnemo[];
extern void(*hook[])(void);

word pc;
byte opcode;
byte b2;
byte b3;

void setMode(enum displayMode mode)
{
    SHOW_MODE = mode;
}

void word2hex(word value)
{
    switch(SHOW_MODE)
    {
        case MODE_ASM:
            printf("$%04X", value);
            break;
        case MODE_TEXAS:
            printf("0h%04x", value);
            break;
        case MODE_BASIC:
            printf("&h%04x", value);
            break;
        case MODE_C:
            printf("0x%04x", value);
            break;
        case MODE_DECIMAL:
            printf("%d", value);
            break;
        case MODE_FURIOSO:
            printf("%04x", value);
            break;
    }
}

void byte2hex(byte value)
{
    switch(SHOW_MODE)
    {
        case MODE_ASM:
            printf("$%02X", value);
            break;
        case MODE_TEXAS:
            printf("0h%02x", value);
            break;
        case MODE_BASIC:
            printf("&h%02x", value);
            break;
        case MODE_C:
            printf("0x%02x", value);
            break;
        case MODE_DECIMAL:
            printf("%d", value);
            break;
        case MODE_FURIOSO:
            printf("%02x", value);
            break;
    }
}

word getRel(byte rel_jmp)
{
        if(rel_jmp < 128)
            return pc + 2 + rel_jmp;
        else
            return pc + 2 - 256 + rel_jmp;
}

void Add1Value()
{
    printf("%04X %02X       %s ", pc, opcode, mnemo[opcode]);
}

void Add2Values()
{
    printf("%04X %02X %02X    %s ", pc, opcode, b2, mnemo[opcode]);
}

void Add3Values()
{
    printf("%04X %02X %02X %02X %s ", pc, opcode, b2, b3, mnemo[opcode]);
}

    //----------------//
    // Mnemonic Hooks //
    //----------------//

void immediate()
{
    b2 = desassGetNextByte();
    Add2Values();
    printf("#");
    byte2hex(b2);
    printf("\n");
}

void inherent()
{
    Add1Value();
    printf("\n");
}

void zeropage()
{
    b2 = desassGetNextByte();
    Add2Values();
    byte2hex(b2);
    printf("\n");
}

void zeropagex()
{
    b2 = desassGetNextByte();
    Add2Values();
    byte2hex(b2);
    printf(",X\n");
}

void zeropagey()
{
    b2 = desassGetNextByte();
    Add2Values();
    byte2hex(b2);
    printf(",Y\n");
}

void indzerox()
{
    b2 = desassGetNextByte();
    Add2Values();
    printf("(");
    byte2hex(b2);
    printf(",X)\n");
}

void indzeroy()
{
    b2 = desassGetNextByte();
    Add2Values();
    printf("(");
    byte2hex(b2);
    printf("),Y\n");
}

void absolute()
{
    b2 = desassGetNextByte();
    b3 = desassGetNextByte();
    Add3Values();
    word2hex(b3*256+b2);
    printf("\n");
}

void absolx()
{
    b2 = desassGetNextByte();
    b3 = desassGetNextByte();
    Add3Values();
    word2hex(b3*256+b2);
    printf(",X\n");
}

void absoly()
{
    b2 = desassGetNextByte();
    b3 = desassGetNextByte();
    Add3Values();
    word2hex(b3*256+b2);
    printf(",Y\n");
}

void indirect()
{
    b2 = desassGetNextByte();
    b3 = desassGetNextByte();
    Add3Values();
    printf("(");
    word2hex(b3*256+b2);
    printf(")\n");
}

void relative()
{
    b2 = desassGetNextByte();
    Add2Values();
    word2hex(getRel(b2));
    printf("\n");
}

void desassOneLine(word addr)
{
    desassSetAddr(addr);
    pc = addr;
    opcode = desassGetNextByte();
    hook[opcode]();
}

void desass(word addr, word nb_lines)
{
    desassSetAddr(addr);
    while(nb_lines--)
    {
        addr = desassGetAddr();
        desassOneLine(addr);
    }
}

const char* mnemo[] =
{
    "BRK", "ORA", "???", "???", "???", "ORA", "ASL", "???", "PHP", "ORA", "ASL", "???", "???", "ORA", "ASL", "???", 
    "BPL", "ORA", "???", "???", "???", "ORA", "ASL", "???", "CLC", "ORA", "???", "???", "???", "ORA", "ASL", "???", 
    "JSR", "AND", "???", "???", "BIT", "AND", "ROL", "???", "PLP", "AND", "ROL", "???", "BIT", "AND", "ROL", "???", 
    "BMI", "AND", "???", "???", "???", "AND", "ROL", "???", "SEC", "AND", "???", "???", "???", "ORA", "ASL", "???", 
    "RTI", "EOR", "???", "???", "???", "EOR", "LSR", "???", "PHA", "EOR", "LSR", "???", "JMP", "EOR", "LSR", "???", 
    "BVC", "EOR", "???", "???", "???", "EOR", "LSR", "???", "CLI", "EOR", "???", "???", "???", "EOR", "LSR", "???", 
    "RTS", "ADC", "???", "???", "???", "ADC", "ROR", "???", "PLA", "ADC", "ROR", "???", "JMP", "ADC", "ROR", "???", 
    "BCS", "ADC", "???", "???", "???", "ADC", "ROR", "???", "SEI", "ADC", "???", "???", "???", "ADC", "ROR", "???", 
    "???", "STA", "???", "???", "STY", "STA", "STX", "???", "DEY", "???", "TXA", "???", "STY", "STA", "STX", "???", 
    "BCC", "STA", "???", "???", "STY", "STA", "STX", "???", "TYA", "STA", "TXS", "???", "???", "STA", "???", "???", 
    "LDY", "LDA", "LDX", "???", "LDY", "LDA", "LDX", "???", "TAY", "LDA", "TAX", "???", "LDY", "LDA", "LDX", "???", 
    "BCS", "LDA", "???", "???", "LDY", "LDA", "LDX", "???", "CLV", "LDA", "TSX", "???", "LDY", "LDA", "LDX", "???", 
    "CPY", "CMP", "???", "???", "CPY", "CMP", "DEC", "???", "INY", "CMP", "DEX", "???", "CPY", "CMP", "DEC", "???", 
    "BNE", "CMP", "???", "???", "???", "CMP", "DEC", "???", "CLD", "CMP", "???", "???", "???", "CMP", "DEC", "???", 
    "CPX", "SBC", "???", "???", "CPX", "SBC", "INC", "???", "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "???", 
    "BEQ", "SBC", "???", "???", "???", "SBC", "INC", "???", "SED", "SBC", "???", "???", "???", "SBC", "INC", "???", 
};

void(*hook[])(void) = 
{
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   inherent,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
    absolute,   indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
    inherent,   indzerox,   inherent,   inherent,   inherent,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   indirect,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
    inherent,   indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent,
    inherent,   inherent,   inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagey,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     inherent,   inherent,
    immediate,  indzerox,   immediate,  inherent,   zeropage,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   zeropagex,  zeropagex,  zeropagey,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absoly,     inherent,
    immediate,  indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
    immediate,  indzerox,   inherent,   inherent,   zeropage,   zeropage,   zeropage,   inherent,
    inherent,   immediate,  inherent,   inherent,   absolute,   absolute,   absolute,   inherent,
    relative,   indzeroy,   inherent,   inherent,   inherent,   zeropagex,  zeropagex,  inherent,
    inherent,   absoly,     inherent,   inherent,   inherent,   absolx,     absolx,     inherent,
};

