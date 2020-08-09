
#include "memory.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define MEMORY_ATARI_FILE_SIGNATURE 0xffff
#define MEMORY_ATARI_FILE_NB_SHOWED 8

byte memory[MEMORY_SIZE];
bool memBreaks[MEMORY_SIZE];
byte memType[MEMORY_SIZE];
void (*memOutputs[MEMORY_SIZE])(byte value);
byte (*memInputs[MEMORY_SIZE])(void);

void memSetInput(word addr, byte(*hook)(void))
{
    memInputs[addr] = hook;
    
    if(memType[addr] == MEMORY_OUTPUT)
        memType[addr] = MEMORY_INOUT;
    else
        memType[addr] = MEMORY_INPUT;
}

void memSetOutput(word addr, void(*hook)(byte value))
{
    memOutputs[addr] = hook;

    if(memType[addr] == MEMORY_INPUT)
        memType[addr] = MEMORY_INOUT;
    else
        memType[addr] = MEMORY_OUTPUT;
}

void memSetRom(int addr, int size)
{
    if((addr + size ) > MEMORY_SIZE)
    {
        printf("Memory bloc out of range!\n");
        return;
    }
    
    while(size--)
    {
        memType[addr] = MEMORY_ROM;
        memory[addr] = ROM_DEFAULT_BYTE;
        addr++;
    }
}

void memSetRam(int addr, int size)
{
    if((addr + size ) > MEMORY_SIZE)
    {
        printf("Memory bloc out of range!\n");
        return;
    }
    
    while(size--)
        memType[addr++] = MEMORY_RAM;
}

void memSetUnwired(int addr, int size)
{
    if((addr + size ) > MEMORY_SIZE)
    {
        printf("Memory bloc out of range!\n");
        return;
    }
    
    while(size--)
        memType[addr++] = MEMORY_UNWIRED;
}

bool memIsRam(word addr)
{
    return memType[addr]  == MEMORY_RAM;
}

bool memIsRom(word addr)
{
    return memType[addr]  == MEMORY_ROM;
}

bool memIsInput(word addr)
{
    return memType[addr]  == MEMORY_INPUT;
}

bool memIsOutput(word addr)
{
    return memType[addr]  == MEMORY_OUTPUT;
}

bool memIsIo(word addr)
{
    return memType[addr]  == MEMORY_INOUT;
}

bool memIsUnwired(word addr)
{
    return memType[addr]  == MEMORY_UNWIRED;
}

bool memIsStorage(word addr)
{
    return (memType[addr]  == MEMORY_RAM) || (memType[addr]  == MEMORY_ROM);
}

void memHmap()
{
    int  hi;
    int  lo;
    bool ram;
    bool rom;
    bool input;
    bool output;
    bool io;
    bool unwired;
    word addr;
    
    printf("     000 100 200 300 400 500 600 700 800 900 A00 B00 C00 D00 E00 F00\n");
    printf("--------------------------------------------------------------------\n");
    
    for(hi = 0; hi < MEMORY_SIZE; hi += 256)
    {
        ram = false;
        rom = false;
        input = false;
        output = false;
        io = false;
        unwired = false;
        
        if(!(hi % 0x1000))
            printf("%04x ", hi);
        
        for(lo = 0; lo < 256; lo++)
        {
            addr = hi +lo;
            if(memIsRam(addr))
                ram = true;
            if(memIsRom(addr))
                rom = true;
            if(memIsInput(addr))
                input = true;
            if(memIsOutput(addr))
                output = true;
            if(memIsIo(addr))
                io = true;
            if(memIsUnwired(addr))
                unwired = true;
        }
        if(ram)
            printf("ram ");
        else if(rom)
            printf("ROM ");
        else if(io)
            printf("I/O ");
        else if(input)
            printf("INP ");
        else if(output)
            printf("OUT ");
        else if(unwired)
            printf("--- ");
        else
            printf("internal error, unknown memory type\n");
        
        if((hi % 0x1000) == 0xf00)
            printf("\n");

    }
    printf("\n");
}

void memMap()
{
    int  hi;
    int  lo;
    bool used;
    bool ram;
    word addr;
    
    printf("     000 100 200 300 400 500 600 700 800 900 A00 B00 C00 D00 E00 F00\n");
    printf("--------------------------------------------------------------------\n");
    
    for(hi = 0; hi < MEMORY_SIZE; hi += 256)
    {
        used = false;
        ram = false;
        
        if(!(hi % 0x1000))
            printf("%04x ", hi);
        
        for(lo = 0; lo < 256; lo++)
        {
            addr = hi +lo;
            if(memIsRam(addr))
            {
                ram = true;
                if(memGet(addr))
                    used = true;
            }
        }
        if(used)
            printf("XXX ");
        else if(ram)
            printf("ooo ");
        else
            printf("... ");
        
        if((hi % 0x1000) == 0xf00)
            printf("\n");

    }
    printf("\n");
}

void memDefRam(word addr)
{
    memType[MEMORY_SIZE] = MEMORY_RAM;
}

void memDefRom(word addr)
{
    memType[MEMORY_SIZE] = MEMORY_ROM;
}

void memDefUnwired(word addr)
{
    memType[MEMORY_SIZE] = MEMORY_UNWIRED;
}

void memSetBreak(word addr, bool value)
{
    memBreaks[addr] = value;
}

bool memIsBreak(word addr)
{
    return memBreaks[addr];
}

void memListBreaks()
{
    int addr;
    int cpt = 0;
    
    for(addr=0; addr<MEMORY_SIZE; addr++)
        if(memBreaks[addr])
        {
            printf("%04x ", addr);
            cpt++;
            if(!(cpt % MEMORY_BREAKS_PER_LINE))
                printf("\n");
        }
    if(!cpt)
        printf("No breakpoint found!\n");
    else if(cpt % MEMORY_BREAKS_PER_LINE)
        printf("\n");
}

void memClrBreaks()
{
    int addr;
    
    for(addr=0; addr<MEMORY_SIZE; addr++)
        memBreaks[addr] = false;
}

byte memGet(word addr)
{
    byte value;
    
    switch(memType[addr])
    {
        case MEMORY_RAM:
        case MEMORY_ROM:
            value = memory[addr];
            break;
        case MEMORY_INPUT:
        case MEMORY_INOUT:
            value = memInputs[addr]();
        case MEMORY_UNWIRED:
        case MEMORY_OUTPUT:
            value = MEMORY_UNWIRED_VALUE;
    }
    return value;
}

void memPut(word addr, byte value)
{
    switch(memType[addr])
    {
        case MEMORY_RAM:
            memory[addr] = value;
            break;
        case MEMORY_INPUT:
        case MEMORY_ROM:
        case MEMORY_UNWIRED:
            break;
            value = memInputs[addr]();
        case MEMORY_INOUT:
        case MEMORY_OUTPUT:
            memOutputs[addr](value);
    }
}

void memPutRom(word addr, byte value)
{
    if((memType[addr]) == MEMORY_ROM)
    {
            memory[addr] = value;
    }
}

byte memGetW(word addr)
{
    return memGet(addr) + 256 *  memGet(addr+1);
}

void memPutW(word addr, word value)
{
    memPut(addr, value & 255);
    memPut(addr+1, value / 256);
}

void memPutWRom(word addr, word value)
{
    memPutRom(addr, value & 255);
    memPutRom(addr+1, value / 256);
}

bool memReadWord(word* value_ptr, FILE* fp)
{
    byte lo_byte;
    byte hi_byte;
    byte read_size = 0;

    if (fp == NULL) 
		return MEMORY_FAILURE;

	read_size += fread((&lo_byte), sizeof(byte), 1, fp);
	read_size += fread((&hi_byte), sizeof(byte), 1, fp);
    
    if(read_size != 2)
        return MEMORY_FAILURE;
    
    *value_ptr = lo_byte + 256 * hi_byte;
    return MEMORY_SUCCESS;
}

word memLoadFile(char* fname, word addr, byte mem_type)
{
    FILE *fp;
    word read_size = 0;
    byte value;
    
    fp = fopen(fname, "rb");
    if (fp == NULL) 
    {
		return 0;
    }

    while(!feof(fp))
    {
        if(fread(&value, sizeof(char), 1, fp))
        {
            switch(mem_type)
            {
                case MEMORY_RAM:
                    memPut(addr++, value);
                    break;
                case MEMORY_ROM:
                    memPutRom(addr++, value);
                    break;
                default:
                    break;
            }
        }
    }
    
	fclose(fp);
	return read_size;
}

word memLoadAtariFile(char* fname)
{
    FILE *fp;
    word read_size = 0;
    int count;
    word magic_word;
    word first;
    word last;
    byte value;
    word index;
    word displayed_bytes;
    
    fp = fopen(fname, "rb");
    if (fp == NULL) 
		return 0;

    // magic number
    if(memReadWord(&magic_word, fp) == MEMORY_FAILURE)
    {
        printf("Unexpected end of file\n");
        fclose(fp);
        return read_size;
    }
    read_size += 2;
    
    if(magic_word != MEMORY_ATARI_FILE_SIGNATURE)
    {
        printf("Not an Atari binary file\n");
        fclose(fp);
        return read_size;
    }
    read_size += 2;
    
    // read bloc(s)
    while(1)
    {
        // read bloc start address
        if(memReadWord(&first, fp) == MEMORY_FAILURE)
            return read_size;
        read_size += 2;
        
        // read bloc last address
        if(memReadWord(&last, fp) == MEMORY_FAILURE)
        {
            printf("Unexpected end of file\n");
            fclose(fp);
            return read_size;
        }
        read_size += 2;
        
        if(verboseFlag)
            printf("loading bloc [%04x:%04x]", first, last);
        index = first;
        count = 1 + last - first;

        // read whole bloc
        while(count--)
        {
            if(!fread(&value, sizeof(byte), 1, fp))
            {
                printf("Unexpected end of file\n");
                fclose(fp);
                return read_size;
            }
            memPut(index++, value);
            read_size++;
        }

        if(verboseFlag)
        {
            // display first bytes of bloc
            index = first;
            displayed_bytes = 0;
            while(index <= last)
            {
                printf(" %02X", memGet(index++));
                displayed_bytes++;
                if(displayed_bytes == MEMORY_ATARI_FILE_NB_SHOWED)
                {
                    printf(" ...");
                    break;
                }
            }
            printf("\n");
        }
    }
    
	fclose(fp);
    
    if(verboseFlag) printf("program start address is %04X", memGetW(0x2e0));

	return read_size;
}

