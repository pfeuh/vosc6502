#ifndef DUMP_H
#define DUMP_H

#include "types.h"

#define DUMP_NB_COLUMNS 16
#define DUMP_NB_BYTES 256

//~ #if DUMP_NB_BYTES % DUMP_NB_COLUMNS
//~ # warning DUMP_NB_BYTES should be a multiple of DUMP_NB_COLUMNS!
//~ #endif

extern void dump(word addr, byte(*getbyte_hook)(word addr), word size);

#endif
