#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)
cd ./

#~ cl65 -O -t atari test.asm -o TEST.BIN
cl65 -O -t gamate test.asm -o TEST.BIN
cl65 -O -t atari print.asm -o PRINT.BIN

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION SUCCESSFUL!
fi
