
#include "emulator.h"

word timerMilestone;
word timerRegValue;
word timerRegConf;

void timerSetConf(byte value)
{
    timerRegConf = value;
}

void timerSetHiValue(byte value)
{
    timerRegValue = (timerRegValue & 0xff) | (value << 8); 
}

void timerSetLoValue(byte value)
{
    timerRegValue = (timerRegValue & 0xff00) | value ; 
}

byte timerGetHiValue()
{
    return timerRegValue << 8;
}

byte timerGetLoValue()
{
    return timerRegValue & 0xff;
}

void timerSequencer()
{
    
    
    
    setinterrupt();
}

