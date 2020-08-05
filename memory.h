#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include <stdbool.h>

#define MEMORY_SUCCESS false
#define MEMORY_FAILURE true

#define MEMORY_SIZE 0x10000
#define MEMORY_BREAKS_PER_LINE 8
#define MEMORY_UNWIRED_VALUE 0xff

//~ typedef void(*hook)(byte value);

extern void memSetRom(int addr, int size);
extern void memSetUnwired(int addr, int size);
extern void memSetOutput(word addr, void(*hook)(byte value));
extern void memSetInput(word addr, byte(*hook)(void));

extern bool memIsBreak(word addr);
extern bool memIsRam(word addr);
extern bool memIsRom(word addr);
extern bool memIsInput(word addr);
extern bool memIsOutput(word addr);
extern bool memIsIo(word addr);
extern bool memIsUnwired(word addr);
extern bool memIsStorage(word addr);
extern void memHmap();
extern void memMap();

extern void memDefRam(word addr);
extern void memDefRom(word addr);
extern void memDefUnwired(word addr);

extern void memSetBreak(word addr, bool value);
extern bool memIsBreak(word addr);
extern void memListBreaks();
extern void memClrBreaks();

extern byte memGet(word addr);
extern void memPut(word addr, byte value);
extern byte memGetW(word addr);
extern void memPutW(word addr, word value);

extern word memLoadFile(char* fname, word addr);
extern word memLoadAtariFile(char* fname);

#endif
