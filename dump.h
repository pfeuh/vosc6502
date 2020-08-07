#ifndef DUMP_H
#define DUMP_H

#include "types.h"

#define DUMP_NB_COLUMNS 16
#define DUMP_MAX_BYTES 256

#if DUMP_MAX_BYTES % DUMP_NB_COLUMNS
# warning DUMP_MAX_BYTES should be a multiple of DUMP_NB_COLUMNS!
#endif

extern void dump(word addr, byte(*getbyte_hook)(word addr));

#endif
