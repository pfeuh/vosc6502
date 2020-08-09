
#include "desass6502.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum displayMode SHOW_MODE = MODE_ASM;

#define DESASS_NB_LABEL_ENTRIES 0x10000
char* desasssLabels[DESASS_NB_LABEL_ENTRIES];
// mnenonics table & functions table are at the end of this file
extern const char* mnemo[];
extern void(*hook[])(void);
char desassLabelBuf[80];

#define DESASS_SHORT_LABEL 1
#define DESASS_LONG_LABEL 2
byte desassLabelType; 

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
    if(desasssLabels[value] != NULL)
        printf("%s", desasssLabels[value]);
    else
    {
        switch(SHOW_MODE)
        {
            case MODE_ASM:
                printf("$%04x", value);
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
}

void byte2hex(byte value)
{
    switch(SHOW_MODE)
    {
        case MODE_ASM:
            printf("$%02x", value);
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

void desassPrintLabelLine(word addr)
{
    if(desasssLabels[addr] != NULL)
        printf("              %s:\n", desasssLabels[addr]);
}

void Add1Value()
{
    if(desassLabelType == DESASS_LONG_LABEL)
        printf("%04x %02x           %s ", desassPC, desassOpcode, mnemo[desassOpcode]);
    else
        printf("%02x -- -- %s ", desassOpcode, mnemo[desassOpcode]);
}

void Add2Values()
{
    if(desassLabelType == DESASS_LONG_LABEL)
        printf("%04x %02x %02x        %s ", desassPC, desassOpcode, desassB2, mnemo[desassOpcode]);
    else
        printf("%02x %02x -- %s ", desassOpcode, desassB2, mnemo[desassOpcode]);
}

void Add3Values()
{
    if(desassLabelType == DESASS_LONG_LABEL)
        printf("%04x %02x %02x %02x     %s ", desassPC, desassOpcode, desassB2, desassB3, mnemo[desassOpcode]);
    else
        printf("%02x %02x %02x %s ", desassOpcode, desassB2, desassB3, mnemo[desassOpcode]);
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
    desassLabelType = DESASS_SHORT_LABEL; 
    word old_addr = desassGetAddr();
    desassSetAddr(addr);
    desassPC = addr;
    desassOpcode = desassGetNextByte();
    hook[desassOpcode]();
    desassSetAddr(old_addr);
}

void desass(word nb_lines)
{
    desassLabelType = DESASS_LONG_LABEL; 
    while(nb_lines--)
    {
        desassPC = desassGetAddr();
        desassPrintLabelLine(desassPC);
        desassOpcode = desassGetNextByte();
        hook[desassOpcode]();
    }
}

bool desassAddLabel(char* _label, word addr)
{
    desasssLabels[addr] = strdup(_label);
    
    if(desasssLabels[addr] != NULL)
    {
        return DESASS_SUCCESS;
    }
    else
        return DESASS_FAILURE;
}

bool desassShowLabels()
{
    int addr;
    word count = 0;
    
    for(addr=0; addr<DESASS_NB_LABEL_ENTRIES; addr++)
        if(desasssLabels[addr] != NULL)
        {
            printf("%04x %s\n", addr, desasssLabels[addr]);
            count++;
        }
    
    printf("label(s) found : %04x\n", count);
    
    return DESASS_SUCCESS;
}

bool desassClrLabels()
{
    int addr;
    
    for(addr=0; addr<DESASS_NB_LABEL_ENTRIES; addr++)
        if(desasssLabels[addr] != NULL)
        {
            free(desasssLabels[addr]);
            desasssLabels[addr] = NULL;
        }
    
    return DESASS_SUCCESS;
}

const char* mnemo[] =
{
    "brk", "ora", "???", "???", "???", "ora", "asl", "???", "php", "ora", "asl", "???", "???", "ora", "asl", "???", 
    "bpl", "ora", "???", "???", "???", "ora", "asl", "???", "clc", "ora", "???", "???", "???", "ora", "asl", "???", 
    "jsr", "and", "???", "???", "bit", "and", "rol", "???", "plp", "and", "rol", "???", "bit", "and", "rol", "???", 
    "bmi", "and", "???", "???", "???", "and", "rol", "???", "sec", "and", "???", "???", "???", "ora", "asl", "???", 
    "rti", "eor", "???", "???", "???", "eor", "lsr", "???", "pha", "eor", "lsr", "???", "jmp", "eor", "lsr", "???", 
    "bvc", "eor", "???", "???", "???", "eor", "lsr", "???", "cli", "eor", "???", "???", "???", "eor", "lsr", "???", 
    "rts", "adc", "???", "???", "???", "adc", "ror", "???", "pla", "adc", "ror", "???", "jmp", "adc", "ror", "???", 
    "bcs", "adc", "???", "???", "???", "adc", "ror", "???", "sei", "adc", "???", "???", "???", "adc", "ror", "???", 
    "???", "sta", "???", "???", "sty", "sta", "stx", "???", "dey", "???", "txa", "???", "sty", "sta", "stx", "???", 
    "bcc", "sta", "???", "???", "sty", "sta", "stx", "???", "tya", "sta", "txs", "???", "???", "sta", "???", "???", 
    "ldy", "lda", "ldx", "???", "ldy", "lda", "ldx", "???", "tay", "lda", "tax", "???", "ldy", "lda", "ldx", "???", 
    "bcs", "lda", "???", "???", "ldy", "lda", "ldx", "???", "clv", "lda", "tsx", "???", "ldy", "lda", "ldx", "???", 
    "cpy", "cmp", "???", "???", "cpy", "cmp", "dec", "???", "iny", "cmp", "dex", "???", "cpy", "cmp", "dec", "???", 
    "bne", "cmp", "???", "???", "???", "cmp", "dec", "???", "cld", "cmp", "???", "???", "???", "cmp", "dec", "???", 
    "cpx", "sbc", "???", "???", "cpx", "sbc", "inc", "???", "inx", "sbc", "nop", "sbc", "cpx", "sbc", "inc", "???", 
    "beq", "sbc", "???", "???", "???", "sbc", "inc", "???", "sed", "sbc", "???", "???", "???", "sbc", "inc", "???", 
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

