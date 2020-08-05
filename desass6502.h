#ifndef DESASS_6502_H
#define DESASS_6502_H

#include "types.h"

enum displayMode
{
// number used in comments is decimal 4660
    MODE_ASM,     // $1234 
    MODE_TEXAS,   // 0h1234
    MODE_BASIC,   // &h1234
    MODE_C,       // 0x1234
    MODE_DECIMAL, // 4660
    MODE_FURIOSO, // 1234
};

extern void desassSetMode(enum displayMode mode);
extern void desass(word addr, word nb_lines);

// these functions have to be provided by the application
extern void desassSetAddr(word add);
extern word desassGetAddr();
extern byte desassGetNextByte();

#endif
