#ifndef TIMERS_H
#define TIMERS_H

extern void timerSetConf(byte value);
extern void timerSetHiValue(byte value);
extern void timerSetLoValue(byte value);
extern byte timerGetHiValue();
extern byte timerGetLoValue();

extern void timerSequencer();

#endif
