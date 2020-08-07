
#include "desass6502.h"
#include <stdio.h>

enum displayMode SHOW_MODE = MODE_ASM;

// mnenonics table & functions table are at the end of this file
extern const char* mnemo[];
extern void(*hook[])(void);

word desassPC;
byte desassOpcode;
byte desassB2;
byte desassB3;

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
            return desassPC + 2 + rel_jmp;
        else
            return desassPC + 2 - 256 + rel_jmp;
}

void Add1Value()
{
    printf("%04X %02X       %s ", desassPC, desassOpcode, mnemo[desassOpcode]);
}

void Add2Values()
{
    printf("%04X %02X %02X    %s ", desassPC, desassOpcode, desassB2, mnemo[desassOpcode]);
}

void Add3Values()
{
    printf("%04X %02X %02X %02X %s ", desassPC, desassOpcode, desassB2, desassB3, mnemo[desassOpcode]);
}

    //----------------//
    // Mnemonic Hooks //
    //----------------//

void immediate()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    printf("#");
    byte2hex(desassB2);
    printf("\n");
}

void inherent()
{
    Add1Value();
    printf("\n");
}

void zeropage()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    byte2hex(desassB2);
    printf("\n");
}

void zeropagex()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    byte2hex(desassB2);
    printf(",X\n");
}

void zeropagey()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    byte2hex(desassB2);
    printf(",Y\n");
}

void indzerox()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    printf("(");
    byte2hex(desassB2);
    printf(",X)\n");
}

void indzeroy()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    printf("(");
    byte2hex(desassB2);
    printf("),Y\n");
}

void absolute()
{
    desassB2 = desassGetNextByte();
    desassB3 = desassGetNextByte();
    Add3Values();
    word2hex(desassB3*256+desassB2);
    printf("\n");
}

void absolx()
{
    desassB2 = desassGetNextByte();
    desassB3 = desassGetNextByte();
    Add3Values();
    word2hex(desassB3*256+desassB2);
    printf(",X\n");
}

void absoly()
{
    desassB2 = desassGetNextByte();
    desassB3 = desassGetNextByte();
    Add3Values();
    word2hex(desassB3*256+desassB2);
    printf(",Y\n");
}

void indirect()
{
    desassB2 = desassGetNextByte();
    desassB3 = desassGetNextByte();
    Add3Values();
    printf("(");
    word2hex(desassB3*256+desassB2);
    printf(")\n");
}

void relative()
{
    desassB2 = desassGetNextByte();
    Add2Values();
    word2hex(getRel(desassB2));
    printf("\n");
}

void desassOneLine(word addr)
{
    word old_addr = desassGetAddr();
    desassSetAddr(addr);
    desassPC = addr;
    desassOpcode = desassGetNextByte();
    hook[desassOpcode]();
    desassSetAddr(old_addr);
}

void desass(word nb_lines)
{
    while(nb_lines--)
    {
        desassPC = desassGetAddr();
        desassOpcode = desassGetNextByte();
        hook[desassOpcode]();
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

