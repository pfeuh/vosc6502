#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)
cd ./

cl65 -O -t atari test_opcodes.asm -o TSTOPCO.BIN

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION 1 SUCCESSFUL!
else
echo COMPILATION 1 FAILED!
fi

cl65 -O -t atari 6502tester.asm -o 6502TESTER.BIN

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION 2 SUCCESSFUL!
else
echo COMPILATION 2 FAILED!
fi
